#include "UnityPrefix.h"

#include "ScriptingProfiler.h"
#include "Runtime/Core/Callbacks/GlobalCallbacks.h"
#include "Runtime/Core/Containers/StringBuilder.h"
#include "Runtime/Profiler/ProfilerManager.h"
#include "Runtime/Profiler/Recorder.h"
#include "Modules/Profiler/Public/Profiler.h"
#include "Runtime/Profiler/MemoryProfilerStats.h"
#include "Runtime/Allocator/MemoryManager.h"
#include "Runtime/Scripting/CommonScriptingClasses.h"
#include "Runtime/Scripting/ScriptingObjectOfType.h"
#include "Runtime/ScriptingBackend/ScriptingApi.h"
#include "Runtime/Utilities/Argv.h"
#include "CoreScriptingClasses.h"

#if PLATFORM_PS4 || PLATFORM_XBOXONE || PLATFORM_ANDROID
    #include "Profiler/PlatformProfiler.h"
#else
    #define PLATFORM_PROFILER_SAMPLE_BEGIN(s)
    #define PLATFORM_PROFILER_SAMPLE_END()
#endif

#if PLATFORM_ANDROID

#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <unwind.h>
#include <dlfcn.h>
#include <android/log.h>

namespace
{
	class BacktraceLogger
	{
		static const int c_file_path_size = 1024;
		static const int c_queue_size = 1024;
		static const int c_log_size = 1024;
	public:
		BacktraceLogger(void):m_Head(0),m_Tail(0)
		{
			m_GcCaptureFile[0]=0;
		}
	public:
		void Start(const char* file)
		{
			snprintf(m_GcCaptureFile, c_file_path_size, "%s", file);
			m_GcCaptureFile[c_file_path_size]=0;
		}
		void Log(const char* prefix, size_t idx, const void* addr, const void* raddr, const char* symbol, const char* file)
		{
			if((m_Tail+1)%(c_queue_size+1)==m_Head){
				FILE* fp = fopen(m_GcCaptureFile, "ab+");
				if(NULL!=fp){
					while((m_Head+1)%(c_queue_size+1)!=m_Tail){
						const char* line = m_Buffer[m_Head];
						m_Head=(m_Head+1)%(c_queue_size+1);

						fprintf(fp,"%s\r\n",line);
					}
					fclose(fp);
				}
			}
			snprintf(m_Buffer[m_Tail],c_log_size,"%s #%d:%p %p %s|%s", prefix, idx, addr, raddr, symbol, file);
			m_Buffer[m_Tail][c_log_size]=0;
			m_Tail = (m_Tail+1)%(c_queue_size+1);
		}
		void Flush(void)
		{
			FILE* fp = fopen(m_GcCaptureFile, "ab+");
			if(NULL!=fp){
				while((m_Head+1)%(c_queue_size+1)!=m_Tail){
					const char* line = m_Buffer[m_Head];
					m_Head=(m_Head+1)%(c_queue_size+1);

					fprintf(fp,"%s\r\n",line);
				}
				fclose(fp);
			}
		}
	private:
		char m_GcCaptureFile[c_file_path_size+1];
		char m_Buffer[c_queue_size+1][c_log_size+1];
		int m_Head;
		int m_Tail;
	};

	static BacktraceLogger g_GcLogger;
	static bool g_LogToFile = false;
	static UInt32 g_LogGcAllocMinSize = 0;
	static UInt32 g_LogGcAllocMaxSize = 0;
	static UInt32 g_LogNativeAllocMinSize = 0;
	static UInt32 g_LogNativeAllocMaxSize = 0;
	
	struct BacktraceState
	{
		void** current;
		void** end;
	};

	static _Unwind_Reason_Code unwind_callback(struct _Unwind_Context* context, void* arg)
	{
		BacktraceState* state = static_cast<BacktraceState*>(arg);
		uintptr_t pc = _Unwind_GetIP(context);
		if (pc) {
			if (state->current == state->end) {
				return _URC_END_OF_STACK;
			}
			else {
				*state->current++ = reinterpret_cast<void*>(pc);
			}
		}
		return _URC_NO_REASON;
	}

	static size_t capture_backtrace(void** buffer, size_t max)
	{
		BacktraceState state = { buffer, buffer + max };
		_Unwind_Backtrace(unwind_callback, &state);

		return state.current - buffer;
	}

	static void dump_backtrace(const char* title, const char* prefix, void** buffer, size_t count)
	{
		for (size_t idx = 0; idx < count; ++idx) {
			const void* addr = buffer[idx];
			const void* raddr = 0;
			const char* symbol = "";
			const char* file = "";

			Dl_info info;
			if (dladdr(addr, &info)) {
				raddr = (const void*)((const char*)addr - (const char*)info.dli_fbase);
				if(info.dli_sname)
				    symbol = info.dli_sname;
				if(info.dli_fname)
				    file = info.dli_fname;
			}

			if(g_LogToFile){
				g_GcLogger.Log(prefix, idx, addr, raddr, symbol, file);
			}
			else{
				__android_log_print(ANDROID_LOG_INFO, title, "%s #%d:%p %p %s|%s", prefix, idx, addr, raddr, symbol, file);
			}
		}
	}

	static void backtrace_tologcat(const char* title, const char* prefix)
	{
		const size_t max = 64;
		void* buffer[max];
		dump_backtrace(title, prefix, buffer, capture_backtrace(buffer, max));
	}

	static void info_tologcat(const char* title, const char* prefix)
	{
		if(g_LogToFile){
			g_GcLogger.Log(prefix, 0, 0, 0, "", "");
		}
		else{
			__android_log_print(ANDROID_LOG_INFO, title, "%s #%d:%p %p %s|%s", prefix, 0, 0, 0, "", "");
		}
	}

#if ENABLE_MEM_PROFILER
	class NativeMemoryLogger
	{
	public:
		static void Register(void)
		{
			GetMemoryManager().logAllocation.Register(&LogAllocationStack);
			GetMemoryManager().logDeallocation.Register(&LogDeallocationStack);
		}
		static void LogAllocationStack(const MemoryManager::AllocationLogDetails& details)
		{
			if(g_LogToFile && details.size>=g_LogNativeAllocMinSize && details.size<=g_LogNativeAllocMaxSize){
			    size_t totalAllocatedMemoryAfterAllocation = GetMemoryManager().GetTotalAllocatedMemory();
			    //printf_console("%s (0x%p): %11zu\tTotal: %.2fMB (%zu) in %s:%d\n", details.function, details.ptr, details.size, totalAllocatedMemoryAfterAllocation / (1024.0f * 1024.0f), totalAllocatedMemoryAfterAllocation, details.file, details.line);
			    	
				char prefix[256];
				snprintf(prefix, 255, "mynativealloc[ptr:%p size:%u after_size:%u]", details.ptr, details.size, totalAllocatedMemoryAfterAllocation/(1024*1024));
				prefix[255] = 0;

				backtrace_tologcat("myalloc", prefix);
			}
		}
		static void LogDeallocationStack(void* ptr, size_t size, const char* function)
		{
			if(g_LogToFile && size>=g_LogNativeAllocMinSize && size<=g_LogNativeAllocMaxSize){
			    size_t totalAllocatedMemoryAfterDeallocation = GetMemoryManager().GetTotalAllocatedMemory() - size;
	  		    //printf_console("%s (0x%p): -%11zu\tTotal: %.2fMB (%zu)\n", function, ptr, size, totalAllocatedMemoryAfterDeallocation / (1024.0f * 1024.0f), totalAllocatedMemoryAfterDeallocation);
	  		    
				char prefix[256];
				snprintf(prefix, 255, "mynativedealloc[ptr:%p size:%u after_size:%u]", ptr, size, totalAllocatedMemoryAfterDeallocation/(1024*1024));
				prefix[255] = 0;

				backtrace_tologcat("myalloc", prefix);
			}
		}
	};
#endif //ENABLE_MEM_PROFILER
}

void StartGcLogger(const char* file)
{
	g_LogToFile=true;
	g_GcLogger.Start(file);
#if ENABLE_MEM_PROFILER
	if(g_LogNativeAllocMinSize!=0 || g_LogNativeAllocMaxSize!=0){
		GetMemoryManager().StartLoggingAllocations(g_LogNativeAllocMinSize, true);
	}
#endif
}
void StopGcLogger(void)
{
#if ENABLE_MEM_PROFILER
	GetMemoryManager().StopLoggingAllocations();
#endif
	g_LogToFile=false;
	g_GcLogger.Flush();
}
void SetLogGcAllocSize(UInt32 minSize, UInt32 maxSize)
{
	g_LogGcAllocMinSize = minSize;
	g_LogGcAllocMaxSize = maxSize;
}
void SetLogNativeAllocSize(UInt32 minSize, UInt32 maxSize)
{
	g_LogNativeAllocMinSize = minSize;
	g_LogNativeAllocMaxSize = maxSize;
#if ENABLE_MEM_PROFILER
	if(g_LogToFile && (g_LogNativeAllocMinSize!=0 || g_LogNativeAllocMaxSize!=0)){
		GetMemoryManager().StartLoggingAllocations(g_LogNativeAllocMinSize, true);
	}
#endif
}

#endif //PLATFORM_ANDROID

namespace profiling
{
    static const char* kScriptingThreadsGroupName = "Scripting Threads";

    static ScriptingProfiler * s_ScriptingProfilerInstance = NULL;

    ScriptingProfiler* GetScriptingProfiler()
    {
        return s_ScriptingProfilerInstance;
    }

    ScriptingProfiler::ScriptingProfiler(MemLabelRef label)
        : m_UISystemProfilerClassPtr(SCRIPTING_NULL)
        , m_ScriptingMethodCache(label)
        , m_IsDeepProfilerEnabled(false)
        #if PROFILER_PLATFORM_SUPPORTS_INSTRUMENTATION
        , m_IsInstrumentationProfilerEnabled(false)
        #endif
        , m_MemLabel(label)
    {
        ScriptingProfilerInitialize();

        const bool enableDeepProfiling = HasARGV("deepprofiling");
        SetDeepProfilerEnabled(enableDeepProfiling);

#if PLATFORM_ANDROID		
#if ENABLE_MEM_PROFILER
		NativeMemoryLogger::Register();
#endif
#endif //PLATFORM_ANDROID
    }

    void ScriptingProfiler::Initialize()
    {
        if (s_ScriptingProfilerInstance != NULL)
            return;
        s_ScriptingProfilerInstance = UNITY_NEW_AS_ROOT(ScriptingProfiler, kMemProfiler, "Profiling", "ScriptingProfiler")();
    }

    void ScriptingProfiler::Shutdown()
    {
        if (s_ScriptingProfilerInstance == NULL)
            return;
        UNITY_DELETE(s_ScriptingProfilerInstance, kMemProfiler);
    }

    void ScriptingProfiler::SetDeepProfilerEnabled(bool v)
    {
        m_IsDeepProfilerEnabled = v;
    }

    #if PROFILER_PLATFORM_SUPPORTS_INSTRUMENTATION
    void ScriptingProfiler::SetInstrumentationProfilerEnabled(bool v)
    {
        m_IsInstrumentationProfilerEnabled = v;
    }

    #endif

    Marker* ScriptingProfiler::GetOrCreateSampler(ScriptingMethodPtr method, const char* methodName, ScriptingClassPtr profileKlass, ScriptingMethodPtr profileMethod, Marker::Flags flags)
    {
        // If profileMethod is specified, then we always look it up.
        if (!profileMethod.IsNull())
            method = profileMethod;

        {
            // Try fast path and acquire read lock.
            ReadWriteLock::AutoReadLock lock(m_ScriptingCacheLock);
            ScriptingMethodCache::const_iterator findIt = m_ScriptingMethodCache.find(method.GetBackendMethod());
            if (findIt != m_ScriptingMethodCache.end())
                return findIt->second;
        }

        // If we don't have sampler registered, add it.
        ReadWriteLock::AutoWriteLock lock(m_ScriptingCacheLock);

        core::pair<ScriptingMethodCache::iterator, bool> result = m_ScriptingMethodCache.insert(method.GetBackendMethod(), static_cast<Marker*>(NULL));
        // Check if sampler was added between locks.
        if (!result.second)
            return result.first->second;

        // Create new and put into method cache
        Marker* sampler = CreateScriptingMethodSampler(m_MemLabel, method, methodName, profileKlass, profileMethod, flags);
        result.first->second = sampler;
        return sampler;
    }

    Marker* ScriptingProfiler::GetOrCreateSampler(ScriptingBackendNativeMethodPtr method)
    {
        {
            // Try fast path and acquire read lock.
            ReadWriteLock::AutoReadLock lock(m_ScriptingCacheLock);
            ScriptingMethodCache::const_iterator findIt = m_ScriptingMethodCache.find(method);
            if (findIt != m_ScriptingMethodCache.end())
                return findIt->second;
        }

        // If we don't have sampler registered, add it.
        ReadWriteLock::AutoWriteLock lock(m_ScriptingCacheLock);

        core::pair<ScriptingMethodCache::iterator, bool> result = m_ScriptingMethodCache.insert(method, static_cast<Marker*>(NULL));
        // Can be NULL in case method refers to an ignored sampler(such as Begin/EndSample).
        if (!result.second)
            return result.first->second;

        ScriptingMethodPtr scriptingMethod = scripting_produce_method_from_backend(method);
        const char* methodName = scripting_method_get_name(scriptingMethod);
        if (IsIgnoredProfilerMethod(scriptingMethod, methodName))
            return NULL;

        Marker* sampler = CreateScriptingMethodSampler(m_MemLabel, scriptingMethod, methodName, NULL, NULL, Marker::kScriptEnterLeave);
        result.first->second = sampler;
        return sampler;
    }

    Marker* ScriptingProfiler::CreateScriptingMethodSampler(MemLabelId label, ScriptingMethodPtr method, const char* methodName, ScriptingClassPtr profileKlass, ScriptingMethodPtr profileMethod, profiling::Marker::Flags flags)
    {
        core::StringBuilder nameBuilder(kMemTempAlloc);
        if (profileKlass == NULL)
        {
            const char* klassName = scripting_class_get_name(scripting_method_get_class(method));
            nameBuilder.append(klassName);
            nameBuilder.append(".");
            nameBuilder.append(methodName);
            nameBuilder.append("()");
        }
        else
        {
            const char* klassName = scripting_class_get_name(profileMethod.IsNull() ? scripting_method_get_class(method) : scripting_method_get_class(profileMethod));
            methodName = profileMethod.IsNull() ? methodName : scripting_method_get_name(profileMethod);

            nameBuilder.append(scripting_class_get_name(profileKlass));
            nameBuilder.append(".");

            // The generated class for a coroutine is called "<Start>Iterator_1"
            // We want to extract "Start" and use that as the method name.
            const char* coroutineMethodNameEnd = NULL;
            if (klassName[0] == '<')
                coroutineMethodNameEnd = strchr(klassName, '>');

            if (coroutineMethodNameEnd != NULL)
                nameBuilder.append(klassName + 1, coroutineMethodNameEnd - (klassName + 1));
            else
                nameBuilder.append(klassName);

            nameBuilder.append("() [Coroutine: ");
            nameBuilder.append(methodName);
            nameBuilder.append("]");
        }

        // Create new marker
        Marker* marker = profiling::GetProfilerManagerPtr()->GetOrCreateMarker(kProfilerScripts, nameBuilder.ToString(), flags);

        return marker;
    }

    bool ScriptingProfiler::IsIgnoredProfilerMethod(ScriptingMethodPtr methodPtr, const char* methodName) const
    {
        if (BeginsWith(methodName, "runtime_invoke"))
            return true;

        // Avoid self profiling of Profiler methods
        ScriptingClassPtr methodClass = scripting_method_get_class(methodPtr);
        const CoreScriptingClasses& coreScriptingClasses = GetCoreScriptingClasses();
        // Ignore Unity.Profiling.ProfilerMarker
        if (methodClass == coreScriptingClasses.profilerMarker ||
            methodClass == coreScriptingClasses.profilerMarkerAutoScope)
        {
            return true;
        }
        // Ignore UnityEngine.Profiler/CustomSampler.Begin/End
        if (methodClass == coreScriptingClasses.profiler ||
            methodClass == coreScriptingClasses.customSampler ||
            methodClass == m_UISystemProfilerClassPtr)
        {
            if (BeginsWith(methodName, "Begin"))
                return true;
            if (BeginsWith(methodName, "End"))
                return true;
        }

        return false;
    }

    void ScriptingProfiler::ClearCache()
    {
        ScriptingProfiler* scriptingProfiler = GetScriptingProfiler();
        if (scriptingProfiler == NULL)
            return;

        // Clear methods cache
        {
            ReadWriteLock::AutoWriteLock lock(scriptingProfiler->m_ScriptingCacheLock);
            scriptingProfiler->m_ScriptingMethodCache.clear_dealloc();
        }

        // Erase ignored function ptr cache
        scriptingProfiler->m_UISystemProfilerClassPtr = SCRIPTING_NULL;
    }

    void ScriptingProfiler::LookupIgnoredMethods()
    {
        ScriptingProfiler* scriptingProfiler = GetScriptingProfiler();
        if (scriptingProfiler == NULL)
            return;

        scriptingProfiler->m_UISystemProfilerClassPtr = OptionalType("UnityEngine.dll", "UnityEngine", "UISystemProfilerApi");
    }

#if ENABLE_MONO || ENABLE_IL2CPP
#if ENABLE_MONO

    const int kScriptingProfilerGC = MONO_PROFILE_GC;
#if ENABLE_PROFILER
    const int kScriptingProfilerThreads = MONO_PROFILE_THREADS;
    const int kScriptingProfilerAllocations = MONO_PROFILE_ALLOCATIONS;
    const int kScriptingProfilerEnterLeave = MONO_PROFILE_ENTER_LEAVE;
    #if PROFILER_PLATFORM_SUPPORTS_INSTRUMENTATION
    const int kScriptingProfilerInstrumentationFlags = MONO_PROFILE_JIT_COMPILATION;
    #endif
#endif

    const int kGCStartEvent = 0; // GC_EVENT_START
    const int kGCEndEvent = 5; // GC_EVENT_END

#elif ENABLE_IL2CPP

    const int kScriptingProfilerGC = IL2CPP_PROFILE_GC;
#if ENABLE_PROFILER
    const int kScriptingProfilerThreads = IL2CPP_PROFILE_THREADS;
    const int kScriptingProfilerAllocations = IL2CPP_PROFILE_ALLOCATIONS;
    const int kScriptingProfilerEnterLeave = IL2CPP_PROFILE_ENTER_LEAVE;
#endif

    const int kGCStartEvent = 6; // GC_EVENT_PRE_STOP_WORLD
    const int kGCEndEvent = 9; // GC_EVENT_POST_START_WORLD

#endif

    // Master builds can grab GC collect time through recorders.
#if ENABLE_PROFILER
    const int kScriptingProfilerDefaultFlags = kScriptingProfilerGC | kScriptingProfilerThreads | kScriptingProfilerAllocations;
#else
    const int kScriptingProfilerDefaultFlags = kScriptingProfilerGC;
#endif

    static void sample_mono_shutdown(void *prof)
    {
        // Empty
    }

    PROFILER_INFORMATION_MASTER(gGCCollect, "GC.Collect", kProfilerGC);
    static void gc_alloc_event(void * ptr, int evnt, int generation)
    {
        switch (evnt)
        {
            case kGCStartEvent:
                profiler_begin(&gGCCollect);
                break;
            case kGCEndEvent:
                profiler_end(&gGCCollect);
                break;
        }
#if PLATFORM_ANDROID		
		if(evnt==kGCStartEvent || evnt==kGCEndEvent){
			char prefix[256];
			int64_t usedSize = il2cpp_gc_get_used_size();
			int64_t heapSize = il2cpp_gc_get_heap_size();
			snprintf(prefix, 255, "mygccollect[event:%d used:%llu heap:%llu]", evnt, usedSize, heapSize);
			prefix[255] = 0;

			backtrace_tologcat("myalloc", prefix);
		}
		else if((evnt & 0xc0000000)!=0){
			uint uevnt = (uint)evnt;
			uint flag = ((uevnt & 0xc0000000)>>30);
			uint val = (uevnt & 0x3fffffff);
			char prefix[256];
			int64_t usedSize = il2cpp_gc_get_used_size();
			int64_t heapSize = il2cpp_gc_get_heap_size();
			snprintf(prefix, 255, "mygccollect[event:%d,%x used:%llu heap:%llu]", flag, val, usedSize, heapSize);
			prefix[255] = 0;

			if(flag==1)
				backtrace_tologcat("myalloc", prefix);
			else
				info_tologcat("myalloc", prefix);
		}
#endif //PLATFORM_ANDROID
    }

    PROFILER_SAMPLER1(gGCResize, "GC.Resize", kProfilerGC, SInt64, "New size");
    static void gc_resize_event(void * ptr, SInt64 new_size)
    {
        PROFILER_SAMPLE_WITH_METADATA(gGCResize, new_size);
#if PLATFORM_ANDROID		
		char prefix[256];
		int64_t usedSize = il2cpp_gc_get_used_size();
		int64_t heapSize = il2cpp_gc_get_heap_size();
		if((new_size & 0xc0000000)!=0){
			int64_t flag = ((new_size & 0xc0000000)>>30);
			int64_t val = (new_size & 0x3fffffff);
			switch(flag){
			case 1:{
				int64_t ignore_off = (val & 0x10000000) ? 1 : 0;
				int64_t retry = (val & 0x20000000) ? 1 : 0;
				val = (val & 0x0fffffff);
				snprintf(prefix, 255, "mygcresize[val:%llu,%llu,%llu,%llu used:%llu heap:%llu]", flag, val, ignore_off, retry, usedSize, heapSize);
				prefix[255] = 0;
				backtrace_tologcat("myalloc", prefix);
				}
			break;
			case 2:{
				snprintf(prefix, 255, "mygcresize[val:%llu,%llx used:%llu heap:%llu]", flag, val, usedSize, heapSize);
				prefix[255] = 0;
				backtrace_tologcat("myalloc", prefix);
				}
			break;
			case 3:{
				snprintf(prefix, 255, "mygcresize[val:%llu,%llx used:%llu heap:%llu]", flag, val, usedSize, heapSize);
				prefix[255] = 0;
				info_tologcat("myalloc", prefix);
				}
			break;
			}
		}
		else{
			snprintf(prefix, 255, "mygcresize[size:%llu used:%llu heap:%llu]", new_size, usedSize, heapSize);
			prefix[255] = 0;
			backtrace_tologcat("myalloc", prefix);
		}
#endif //PLATFORM_ANDROID
    }

#if ENABLE_PROFILER
    PROFILER_MARKER(gFinalizer, kProfilerGC, "GC.Finalizer");
    static void finalizer_start(void *prof)
    {
        profiling::Profiler* profiler = profiling::Profiler::GetPtr();
        if (profiler != NULL)
            profiler->InitializeUserThread(kScriptingThreadsGroupName, "Finalizer");

        profiler_begin(&gFinalizer);
    }

    static void finalizer_end(void *prof)
    {
        profiler_end(&gFinalizer);
    }

    static void thread_start(void *prof, unsigned long tid)
    {
        profiling::Profiler* profiler = profiling::Profiler::GetPtr();
        if (profiler != NULL)
        {
            core::string name("#", kMemTempAlloc);
            name += UnsignedInt64ToString(tid);
            profiler->InitializeUserThread(kScriptingThreadsGroupName, name.c_str());
        }
    }

    static void thread_end(void *prof, unsigned long tid)
    {
        profiling::Profiler* profiler = profiling::Profiler::GetPtr();
        if (profiler != NULL)
            profiler->CleanupUserThread();
    }

    static void thread_name(void *prof, uintptr_t tid, const char *name)
    {
        profiling::Profiler* profiler = profiling::Profiler::GetPtr();
        if (profiler != NULL)
            profiler->InitializeUserThread(kScriptingThreadsGroupName, name);
    }

    PROFILER_SAMPLER1(gGCAlloc, "GC.Alloc", kProfilerAllocation, SInt64, "size");
    static void sample_allocation(void* pr, ScriptingBackendNativeObjectPtr obj, ScriptingBackendNativeClassPtr klass)
    {
#if PLATFORM_ANDROID	
        UInt32 objSize = scripting_object_get_size(obj);
		if(g_LogToFile && objSize>=g_LogGcAllocMinSize && objSize<=g_LogGcAllocMaxSize){
			char prefix[256];
			int64_t usedSize = il2cpp_gc_get_used_size();
			int64_t heapSize = il2cpp_gc_get_heap_size();
			snprintf(prefix, 255, "mygcalloc[size:%u used:%llu heap:%llu]", objSize, usedSize, heapSize);
			prefix[255] = 0;

			backtrace_tologcat("myalloc", prefix);
		}
#endif //PLATFORM_ANDROID
        // Avoid function calls when we are not interested in the event.
        profiling::Profiler* profiler = profiling::Profiler::GetActivePtr();
        if (gGCAlloc.GetCallback() == NULL && profiler == NULL)
            return;

        UInt32 size = scripting_object_get_size(obj);
        profiler_begin_with_metadata(&gGCAlloc, size);

        // Avoid function calls when profiler is disabled.
        if (profiler != NULL)
        {
            profiler_add_callstack_to_sample();
            GetMemoryProfilerStats().RegisterGCAllocation(size);
        }

        profiler_end(&gGCAlloc);
    }

    static inline void enter_leave_mono_sample(ScriptingBackendNativeMethodPtr method, bool enter)
    {
        profiling::Profiler* profiler = profiling::Profiler::GetActivePtr();
        if (profiler == NULL)
            return;

        ScriptingProfiler* instance = GetScriptingProfiler();
        if (instance == NULL)
            return;

        Marker* sampler = instance->GetOrCreateSampler(method);
        // Sampler is set to NULL if it should be ignored
        if (sampler == NULL)
            return;

        // Begin Sample
        profiler->EmitSample(sampler->GetID(), enter ? proto::kBeginSample : proto::kEndSample);
    }

    static void enter_mono_sample(void* pr, ScriptingBackendNativeMethodPtr method)
    {
        enter_leave_mono_sample(method, true);
    }

    static void leave_mono_sample(void* pr, ScriptingBackendNativeMethodPtr method)
    {
        enter_leave_mono_sample(method, false);
    }

#endif // ENABLE_PROFILER
#endif // ENABLE_MONO || ENABLE_IL2CPP

    // Called when scripting is initialized and we can install callbacks.
    void ScriptingProfiler::ScriptingProfilerInitialize()
    {
        if (!profiler_is_available())
            return;

#if ENABLE_MONO || ENABLE_IL2CPP
        scripting_profiler_install(NULL, sample_mono_shutdown);
        // Get GC.Collect and GC.Resize events in non-dev players.
        scripting_profiler_install_gc(gc_alloc_event, gc_resize_event);

#if ENABLE_PROFILER
        scripting_profiler_install_thread(thread_start, thread_end);
        scripting_profiler_install_thread_name(thread_name);
        scripting_profiler_install_gc_finalizing(finalizer_start);
        scripting_profiler_install_gc_finalized(finalizer_end);
        scripting_profiler_install_allocation(sample_allocation);

        //#if PROFILER_PLATFORM_SUPPORTS_INSTRUMENTATION
        //    profiling::InstrumentationManager::Get().InitializeMonoJitCallbacks();
        //    if (m_IsInstrumentationProfilerEnabled)
        //        flags |= kScriptingProfilerInstrumentationFlags;
        //#endif

        // Deep profiling will only be available in editor
        scripting_profiler_install_enter_leave(enter_mono_sample, leave_mono_sample);
#endif // ENABLE_PROFILER
#endif // ENABLE_MONO || ENABLE_IL2CPP

        // Setup domain reload callbacks
        REGISTER_GLOBAL_CALLBACK(beforeDomainUnload, "ScriptingProfiler.ClearCache", ScriptingProfiler::ClearCache());
        REGISTER_GLOBAL_CALLBACK(didLoadAllAssemblies, "ScriptingProfiler.LookupIgnoredMethods", ScriptingProfiler::LookupIgnoredMethods());
    }

    //Called on monoreload
    void ScriptingProfiler::UpdateRegisteredScriptingEvents()
    {
        if (!profiler_is_available())
            return;

#if ENABLE_MONO || ENABLE_IL2CPP
        int flags = kScriptingProfilerDefaultFlags;

#if ENABLE_PROFILER
        //#if PROFILER_PLATFORM_SUPPORTS_INSTRUMENTATION
        //    profiling::InstrumentationManager::Get().InitializeMonoJitCallbacks();
        //    if (m_IsInstrumentationProfilerEnabled)
        //        flags |= kScriptingProfilerInstrumentationFlags;
        //#endif

        if (m_IsDeepProfilerEnabled)
            flags |= kScriptingProfilerEnterLeave;
#endif // ENABLE_PROFILER

        scripting_profiler_set_events(flags);
#endif // ENABLE_MONO || ENABLE_IL2CPP
    }
} // end profiling

#if ENABLE_PROFILER

profiling::Marker* scripting_invoke_profiler_begin(ScriptingMethodPtr method, ScriptingClassPtr profileKlass, ScriptingMethodPtr profileMethod, ScriptingObjectPtr instance)
{
    profiling::Profiler* profiler = profiling::Profiler::GetActivePtr();
    if (profiler == NULL)
        return NULL;

    // Extract object for profiler
    InstanceID objInstanceID = InstanceID_None;
    if (CurrentThreadIsMainThread() && instance)
    {
        // Extracting of object from scripting reference supported only on a main thread
        ScriptingClassPtr instanceClass = scripting_object_get_class(instance);
        if (scripting_class_has_parent(instanceClass, GetCoreScriptingClasses().object))
        {
            Object* objPtr = ScriptingObjectOfType<Object>(instance).GetPtr();
            if (objPtr != NULL)
                objInstanceID = objPtr->GetInstanceID();
        }
    }

    profiling::ScriptingProfiler* scriptingProfiler = profiling::GetScriptingProfiler();
    if (scriptingProfiler == NULL)
        return NULL;

    profiling::Marker* sampler = scriptingProfiler->GetOrCreateSampler(method, scripting_method_get_name(method), profileKlass, profileMethod, profiling::Marker::kScriptMonoRuntimeInvoke);
    if (sampler == NULL)
        return NULL;

    profiler_begin_instance_id(sampler, objInstanceID);

    return sampler;
}

#endif // ENABLE_PROFILER
