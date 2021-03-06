#include "UnityPrefix.h"
#include "Configuration/UnityConfigure.h"
#include "MonoICallRegistration.h"
#include "Runtime/Modules/ModuleRegistration.h"

// Generated by BuildPlayer for AOT platforms when we want
// to take advantage of dead code stripping of C++ code
void RegisterAllStrippedInternalCalls();

#if INTERNAL_CALL_STRIPPING

void RegisterAllInternalCalls()
{
    RegisterAllStrippedInternalCalls();
}

#else

#if UNITY_EDITOR
void ExportEditorSpriteAtlasBindingsNew();
void ExportAudioImporterBindingsNew();
void ExportVideoImporterBindingsNew();
void ExportModelImporterBindingsNew();
void ExportMonoImporterBindingsNew();
void ExportMovieImporterBindingsNew();
void ExportPlayerSettingsSplashScreenEditorBindingsNew();
void ExportPlayerSettingsSplashScreenBindingsNew();
void ExportShaderImporterBindingsNew();
void ExportTextureImporterBindingsNew();
void ExportBumpMapSettingsBindingsNew();
void ExportTextureUtilBindingsNew();
void ExportTextureImporterTypesBindingsNew();
void ExportChangeTrackerHandleBindingsNew();
void ExportEditorConnectionInternalBindings();
void ExportMediaEncoderBindingsNew();
void ExportGameObjectRecorderBindingsNew();
void ExportPrefabImporterBindingsNew();
void ExportEditorAssembliesBindingsNew();
void ExportCompilationPipelineBindingsNew();
void ExportVCProviderBindingsNew();
void ExportVCMessageBindingsNew();
void ExportVCCustomCommandBindingsNew();
void ExportVCPluginBindingsNew();
void ExportVCTaskBindingsNew();
void ExportVCAssetBindingsNew();
void ExportVCConflictItemBindingsNew();
void ExportVCMergeResultBindingsNew();
void ExportVCChangeSetBindingsNew();
void ExportObjectFactoryBindingsNew();
void ExportLightingDataAssetBindingsNew();
void ExportLightmappingBindingsNew();
void ExportLightmapVisualizationBindingsNew();
void ExportLightProbeVisualizationBindingsNew();
void ExportPlayablesBindingsNew();
void ExportSpriteEditorExtensionBindingsNew();
void ExportTextureGeneratorBindingsNew();
void ExportBuiltinBakedReflectionSystemBindingsNew();
void ExportScriptableBakedReflectionSystemWrapperBindingsNew();
void ExportAssetsMenuUtilityBindingsNew();
void ExportIconUtilityBindingsNew();
void ExportTagManagerBindingsNew();
void ExportPerformanceBindingsNew();
void ExportStageUtilityBindingsNew();
#endif
void ExportBuiltinRuntimeReflectionSystemBindingsNew();
void ExportScriptableRuntimeReflectionSystemSettingsBindingsNew();

void ExportCrashReportBindingsNew();
void ExportUnhandledExceptionHandlerBindingsNew();
void ExportSystemInfoBindingsNew();
void ExportCoroutineBindingsNew();
void ExportScriptableObjectBindingsNew();
#if ENABLE_CACHING
void ExportCachingBindingsNew();
void ExportCacheBindingsNew();
#endif
void ExportLayerMaskBindingsNew();
void ExportSortingLayerBindingsNew();
void ExportSpriteAtlasBindingsNew();
void ExportGradientBindingsNew();
void ExportCullingGroupBindingsNew();
void ExportNoAllocHelpersBindingsNew();
void ExportGraphicsManagersBindingsNew();
void ExportGraphicsRenderersBindingsNew();
void ExportGraphicsComponentsBindingsNew();
void ExportGraphicsSettingsBindingsNew();
void ExportGraphicsBindingsNew();
void ExportSplashScreenBindingsNew();
void ExportMeshBindingsNew();
void ExportReflectionProbeBindingsNew();
void ExportTextureBindingsNew();
void ExportGraphicsFormatUtilityBindingsNew();
void ExportGUIElementBindingsNew();
void ExportHandheldBindingsNew();
void ExportGUIViewDebuggerHelperBindingsNew();
void ExportGizmosBindingsNew();
void ExportColorUtilityBindingsNew();
void ExportMathBindingsNew();
void ExportAnimationCurveBindingsNew();
void ExportUNETworkingBindings();
void ExportTextAssetBindingsNew();
void ExportScriptingRuntimeBindingsNew();
void ExportGarbageCollectorBindingsNew();
void ExportEditorUtilityBindingsNew();
void ExportDragAndDropBindingsNew();
void ExportHelpBindingsNew();
void ExportMenuBindingsNew();
void ExportSelectionBindingsNew();
void ExportEditorPrefsBindingsNew();
void ExportUnsupportedBindingsNew();
void ExportAnimationRecorderBindings();
void ExportObjectNamesBindingsNew();
void ExportUnityStatsBindings();
// m1 code
void ExportUnityStats2Bindings();
void ExportUnityM1ExtensionBindings();
void ExportMonoScriptBindingsNew();
void ExportAsyncProgressBarBindingsNew();
void ExportAnimationCurvePreviewCacheBindingsNew();
void ExportGradientPreviewCacheBindingsNew();
void ExportUsabilityAnalyticsBindingsNew();
void ExportOSColorPickerBindingsNew();
void ExportiOSDeviceBindingsNew();
void ExportiOSNotificationsBindingsNew();
void ExportiOSReplayKitBindingsNew();
void ExporttvOSBindingsNew();
void ExportPackageUtilityBindingsNew();
void ExportActiveEditorTrackerBindingsNew();
void ExportEditorUserBuildSettingsBindingsNew();
void ExportEditorBuildSettingsBindingsNew();
void ExportHandlesBindingsNew();
void ExportHandleUtilityBindingsNew();
void ExportEditorGUIUtilityBindingsNew();
void ExportSavedGUIStateBindingsNew();
void ExportEditorResourcesBindingsNew();
void ExportInternalUtilityBindings();
void ExportStaticOcclusionCullingBindingsNew();
void ExportUnwrappingBindingsNew();
void ExportIHVImageFormatImporterBindingsNew();
void ExportTerrainInspectorUtilBindingsNew();
void ExportOSUtilBindingsNew();
void ExportInternalMeshUtilBindingsNew();
void ExportVideoUtilBindingsNew();
void ExportModuleMetadataBindings();
void ExportLogEntriesBindingsNew();
void ExportUnityTypeBindingsNew();
void ExportWebURLsBindingsNew();
#if INCLUDE_GI
void ExportLightmappingBindingsNew();
#endif
#if INCLUDE_GI && INCLUDE_DYNAMIC_GI
void ExportLightmapParametersBindingsNew();
#endif
void ExportPluginImporterBindingsNew();
void ExportShaderUtilBindings();
void ExportShaderUtilBindingsNew();
void ExportShaderKeywordBindingsNew();
void ExportMeshUtilityBindingsNew();
void ExportPrefabUtilityBindingsNew();
void ExportEditorApplicationBindingsNew();
void ExportBuildPipelineBindingsNew();
void ExportSerializedObjectBindings();
void ExportSerializedObjectBindingsNew();
void ExportSerializedPropertyBindingsNew();
void ExportSerializedObjectChangeTrackerBindingsNew();
void ExportAssetDatabaseBindings();
void ExportAssetDatabaseBindingsNew();
void ExportUtility_WIPBindings();
void ExportAnimationUtilityBindingsNew();
void ExportAnimationModeBindingsNew();
void ExportStateMachineBindings();
void ExportStateMachineBindingsNew();
void ExportMuscleClipUtilityBindingsNew();
void ExportAnimatorControllerBindingsNew();
void ExportStateMachineBehaviourContextBindingsNew();
void ExportAnimatorControllerLayerBindingsNew();
void ExportBlendTreeBindingsNew();
void ExportEditorWindowBindingsNew();
void ExportGUIViewBindingsNew();
void ExportContainerWindowBindingsNew();
void ExportWebViewBindings();
void ExportAvatarUtilityBindingsNew();
void ExportBlendTreePreviewUtilityBindingsNew();
void ExportAssetStoreUtilsBindings();
void ExportAssetStoreToolUtilsBindings();
void ExportProfilerAPIBindings();
void ExportProfilerFrameDataViewBindingsNew();
void ExportPlayerLoopBindingsNew();
void ExportPlayerSettingsBindingsNew();
void ExportPlayerSettingsAndroidBindingsNew();
void ExportPlayerSettingsPlatformIconsBindingsNew();
void ExportPlayerSettingsFacebookBindingsNew();
void ExportPlayerSettingsIOSBindingsNew();
void ExportPlayerSettingsTVOSBindingsNew();
void ExportPlayerSettingsMacOSBindingsNew();
void ExportPlayerSettingsLuminBindings();
void ExportPlayerSettingsPS4BindingsNew();
void ExportPlayerSettingsWSABindingsNew();
void ExportPlayerSettingsXboxOneBindingsNew();
void ExportPlayerSettingsWebGLBindings();
void ExportPlayerSettingsSwitchBindingsNew();
void ExportPlayerSettingsVRGoogleBindings();
void ExportPlayerSettingsVulkanBindingsNew();
void ExportRuntimeInitializeOnLoadManagerBindingsNew();
void ExportXboxServicesBindings();
void ExportXboxKinectBindings();
void ExportXboxAvatarBindings();
void ExportXboxKeyboardBindings();
void ExportXboxVideoModeBindings();
void ExportInternalEditorUtilityBindingsNew();
void ExportEditorMaterialUtilityBindingsNew();
void ExportFileUtilBindingsNew();
void ExportEditorSettingsBindingsNew();
void ExportEditorUserSettingsBindingsNew();
void ExportLightmapEditorSettingsBindingsNew();
void ExportAndroidInputBindingsNew();
void ExportAndroidJNIBindingsNew();
void ExportAnnotationUtilityBindingsNew();
void ExportFlareLayerBindingsNew();
void ExportShaderBindingsNew();
void ExportGradientBindingsNew();
void ExportParticleSystemEditorBindingsNew();
void ExportAsyncOperationBindingsNew();
void ExportApplicationBindingsNew();
void ExportUnityEngineObjectBindingsNew();
void ExportCameraBindingsNew();
void ExportScriptableRenderLoopBindingsNew();
void ExportComponentBindingsNew();
void ExportComputeShaderBindingsNew();
void ExportAsyncGPUReadbackBindingsNew();
void ExportDisplayBindingsNew();
void ExportTransformBindingsNew();
void ExportGameObjectBindingsNew();
void ExportLODBindingsNew();
void ExportTimeBindingsNew();
void ExportBehaviourBindingsNew();
void ExportMonoBehaviourBindingsNew();
void ExportDebugBindingsNew();
void ExportLightBindingsNew();
void ExportLineUtilityBindingsNew();
#if INCLUDE_GI
void ExportDynamicGIBindingsNew();
void ExportGIDebugVisualisationBindingsNew();
#endif
void ExportRandomBindingsNew();
void ExportInputBindingsNew();
void ExportPingBindingsNew();
void ExportPropertyNameBindingsNew();
void ExportSortingGroupBindingsNew();
void ExportPlayerConnectionInternalBindingsNew();
void ExportSpritesBindingsNew();
void ExportSpriteDataAccessBindingsNew();
void ExportSpriteRendererBindingsNew();
void ExportPixelSnappingBindingsNew();
void ExportLODUtilityBindings();
void ExportRenderDocBindingsNew();
void ExportGameObjectUtilityBindingsNew();
void ExportComponentUtilityBindingsNew();
void ExportLightProbeGroupBindingsNew();
void ExportLightProbeProxyVolumeBindingsNew();
void ExportGUIDBindingsNew();
void ExportAsyncHTTPClientBindingsNew();
void ExportAssetStoreContextBindings();
void ExportEditorJsonUtilityBindings();
void ExportHash128BindingsNew();
void ExportUnityEventQueueSystemBindingsNew();
void ExportUnityLogWriterBindingsNew();
void ExportUndoBindingsNew();
void ExportCursorBindingsNew();
void ExportAssetImportContextBindingsNew();
void ExportAssetImporterBindingsNew();
void ExportNativeFormatImporterUtilityBindingsNew();
void ExportAssetPreviewBindingsNew();
void ExportAudioUtilBindings();
void ExportAudioMixerControllerBindings();
void ExportAudioMixerGroupControllerBindings();
void ExportAudioMixerEffectControllerBindings();
void ExportAudioMixerSnapshotControllerBindings();
void ExportAudioMixerDescriptionBindings();
void ExportWaveformStreamerBindingsNew();
void ExportAudioRendererBindingsNew();
void ExportEditorBindingsNew();
void ExportSpritePackerBindingsNew();
void ExportSpritesEditorBindings();
void ExportPolygonEditorBindingsNew();
void ExportBootConfigBindingsNew();
void ExportPlayerPrefsBindingsNew();
void ExportHighlighterBindingsNew();
void ExportRegistryUtilBindingsNew();
void ExportVisualStudioUtilBindingsNew();
void ExportHardwareBindings();
void ExportFrameDebuggerBindings();
void ExportBillboardRendererBindingsNew();
void ExportPlayableHandleBindingsNew();
void ExportPlayableGraphBindingsNew();
void ExportPlayableOutputHandleBindingsNew();
void ExportMaterialEffectPlayableBindingsNew();
void ExportCameraPlayableBindingsNew();
void ExportTextureMixerPlayableBindingsNew();
void ExportTexturePlayableOutputBindingsNew();
void ExportTexturePlayableGraphExtensionsBindingsNew();
void ExportGPUFenceBindingsNew();
void ExportRectTransformBindingsNew();
#if ENABLE_MANAGED_JOBS && ENABLE_MANAGED_TRANSFORM_JOBS
void ExportTransformAccessArrayBindingsNew();
#endif
void ExportSphericalHarmonicsL2BindingsNew();
void ExportResourcesBindingsNew();
void ExportOnDemandResourcesBindingsNew();
#if ENABLE_CLOUD_SERVICES_COLLAB
void ExportCollabBindingsNew();
#endif
#if PLATFORM_WIN
void ExportSpeechBindingsNew();
#endif
#if UNITY_EDITOR || PLATFORM_STANDALONE
void ExportWindowsCrashReportingBindingsNew();
#endif
void ExportAppTrialBindingsNew();
void ExportWindowsFileBindingsNew();
void ExportWindowsDirectoryBindingsNew();
void ExportWindowsCryptoBindingsNew();
void ExportWSAApplicationBindingsNew();
void ExportWSACursorBindingsNew();
void ExportWSATilesBindingsNew();
void ExportWSALauncherBindingsNew();

void ExportRuntimeUndoBindingsNew();
void ExportAndroidPermissionsBindingsNew();

void ExportSpeedTreeImporterBindingsNew();
void ExportDefaultAssetBindingsNew();
void ExportAssetImportInProgressProxyBindingsNew();

#if UNITY_EDITOR
void ExportLocalizationDatabaseBindingsNew();
#endif

void ExportAPIUpdaterManagerBindingsNew();

#if ENABLE_CLOUD_SERVICES
void ExportUnityConnectBindingsNew();
void ExportEditorProjectAccessBindingsNew();
#endif
#if ENABLE_CLOUD_SERVICES_ADS
void ExportAdvertisementSettingsBindingsNew();
#endif
#if ENABLE_CLOUD_SERVICES_ANALYTICS
void ExportAnalyticsSettingsBindingsNew();
#endif
#if ENABLE_CLOUD_SERVICES_PURCHASING
void ExportPurchasingSettingsBindingsNew();
#endif
#if ENABLE_CLOUD_SERVICES_CRASH_REPORTING
void ExportCrashReportingSettingsBindingsNew();
#endif
#if ENABLE_CLOUD_SERVICES_ANALYTICS
void ExportPerformanceReportingSettingsBindingsNew();
#endif
void ExportSceneBindingsNew();
void ExportSceneManagerBindingsNew();
void ExportSceneUtilityBindingsNew();
#if UNITY_EDITOR
void ExportEditorSceneManagerBindingsNew();
void ExportEditorGraphicsSettingsBindingsNew();
void ExportDrivenPropertyManagerInternalBindingsNew();
void ExportHomeWindowBindingsNew();
void ExportBurstCompilerServiceBindingsNew();
void ExportMemorySnapshotFileWriterBindingsNew();
#endif
void ExportProfilerBindingsNew();
void ExportSamplerBindingsNew();
void ExportProfilerMarkerBindingsNew();
void ExportDrivenPropertyManagerBindingsNew();
void ExportRecorderBindingsNew();
void ExportUnsafeUtilityBindingsNew();
void ExportAtomicSafetyHandleBindingsNew();

#if ENABLE_MARSHALLING_TESTS
// This functions are STRICTLY for test purposes. The point is to test the managed->native call through the
// BindingsGenerator. There is currently no alternative way to test this, than to have test classes lying around.
void ExportMarshallingTestsBindingsNew();
#endif

void ExportAsyncReadManagerBindingsNew();

void ExportRenderPassAttachmentBindingsNew();
void ExportScriptableRenderContextBindingsNew();
void ExportRenderingCommandBufferBindingsNew();
void ExportDiagnosticsUtilsBindingsNew();
void ExportMemoryProfilingBindingsNew();

typedef void InternallCallMethod ();
static InternallCallMethod* sMonoBindingsRegistration[] =
{
#if ENABLE_MARSHALLING_TESTS
    &ExportMarshallingTestsBindingsNew,
#endif

    &ExportSystemInfoBindingsNew,
    &ExportCoroutineBindingsNew,
    &ExportScriptableObjectBindingsNew,
    &ExportLayerMaskBindingsNew,
    &ExportSortingLayerBindingsNew,
    &ExportCrashReportBindingsNew,
    &ExportUnhandledExceptionHandlerBindingsNew,
#if ENABLE_CACHING
    &ExportCachingBindingsNew,
    &ExportCacheBindingsNew,
#endif
    &ExportGradientBindingsNew,
    &ExportCullingGroupBindingsNew,
    &ExportNoAllocHelpersBindingsNew,
    &ExportGraphicsManagersBindingsNew,
    &ExportGraphicsRenderersBindingsNew,
    &ExportGraphicsComponentsBindingsNew,
    &ExportGraphicsSettingsBindingsNew,
    &ExportGraphicsBindingsNew,
    &ExportSplashScreenBindingsNew,
    &ExportMeshBindingsNew,
    &ExportReflectionProbeBindingsNew,
    &ExportTextureBindingsNew,
    &ExportGraphicsFormatUtilityBindingsNew,
    &ExportGUIElementBindingsNew,
    &ExportGizmosBindingsNew,
    &ExportFlareLayerBindingsNew,
    &ExportColorUtilityBindingsNew,
    &ExportMathBindingsNew,
    &ExportAnimationCurveBindingsNew,
    &ExportAsyncOperationBindingsNew,
    &ExportUnityEngineObjectBindingsNew,
    &ExportCameraBindingsNew,
    &ExportScriptableRenderLoopBindingsNew,
    &ExportComponentBindingsNew,
    &ExportComputeShaderBindingsNew,
    &ExportAsyncGPUReadbackBindingsNew,
    &ExportGameObjectBindingsNew,
    &ExportMonoBehaviourBindingsNew,
    &ExportTransformBindingsNew,
    &ExportLODBindingsNew,
    &ExportTimeBindingsNew,
    &ExportShaderBindingsNew,
    &ExportBehaviourBindingsNew,
    &ExportDebugBindingsNew,
    &ExportDisplayBindingsNew,
    &ExportLightBindingsNew,
    &ExportLineUtilityBindingsNew,
#if INCLUDE_GI
    &ExportDynamicGIBindingsNew,
    &ExportGIDebugVisualisationBindingsNew,
#endif
    &ExportRandomBindingsNew,
    &ExportInputBindingsNew,
    &ExportApplicationBindingsNew,
    &ExportSortingGroupBindingsNew,
    &ExportSpritesBindingsNew,
    &ExportSpriteDataAccessBindingsNew,
    &ExportSpriteRendererBindingsNew,
    &ExportPixelSnappingBindingsNew,
    &ExportSpriteAtlasBindingsNew,
    &ExportLightProbeGroupBindingsNew,
#if UNITY_EDITOR
    &ExportLightingDataAssetBindingsNew,
    &ExportLightmappingBindingsNew,
    &ExportLightmapVisualizationBindingsNew,
    &ExportLightProbeVisualizationBindingsNew,
    &ExportBuiltinBakedReflectionSystemBindingsNew,
    &ExportScriptableBakedReflectionSystemWrapperBindingsNew,
#endif
    &ExportBuiltinRuntimeReflectionSystemBindingsNew,
    &ExportScriptableRuntimeReflectionSystemSettingsBindingsNew,
    &ExportLightProbeProxyVolumeBindingsNew,
    &ExportCursorBindingsNew,
    &ExportBootConfigBindingsNew,
    &ExportPlayerPrefsBindingsNew,
    &ExportBillboardRendererBindingsNew,
    &ExportPlayableHandleBindingsNew,
    &ExportPlayableGraphBindingsNew,
    &ExportPlayableOutputHandleBindingsNew,
    &ExportCameraPlayableBindingsNew,
    &ExportMaterialEffectPlayableBindingsNew,
    &ExportTextureMixerPlayableBindingsNew,
    &ExportTexturePlayableGraphExtensionsBindingsNew,
    &ExportTexturePlayableOutputBindingsNew,
    &ExportGPUFenceBindingsNew,
    &ExportRectTransformBindingsNew,
#if ENABLE_MANAGED_JOBS && ENABLE_MANAGED_TRANSFORM_JOBS
    &ExportTransformAccessArrayBindingsNew,
#endif
    &ExportSphericalHarmonicsL2BindingsNew,
    &ExportRuntimeUndoBindingsNew,
    &ExportResourcesBindingsNew,
    &ExportAndroidPermissionsBindingsNew,
    &ExportPropertyNameBindingsNew,

///@TODO: Remove all #ifdefs. We are doing everything via defines in the generated cpp files.
#if ENABLE_NETWORK
    #if !(PLATFORM_SWITCH || PLATFORM_WIIU)
    &ExportPingBindingsNew,
    #endif
    //&ExportUNETworkingBindings,
#endif
    &ExportTextAssetBindingsNew,
    &ExportHash128BindingsNew,
    &ExportUnityEventQueueSystemBindingsNew,
    &ExportUnityLogWriterBindingsNew,
    &ExportPlayerConnectionInternalBindingsNew,
    &ExportScriptingRuntimeBindingsNew,
    &ExportGarbageCollectorBindingsNew,
#if UNITY_IPHONE_API
    &ExportiOSDeviceBindingsNew,
    &ExportiOSNotificationsBindingsNew,
    &ExportiOSReplayKitBindingsNew,
    &ExporttvOSBindingsNew,
    &ExportOnDemandResourcesBindingsNew,
#endif

#if UNITY_IPHONE_API || UNITY_ANDROID_API || PLATFORM_WINRT || UNITY_SWITCH_API
    &ExportHandheldBindingsNew,
#endif

#if UNITY_ANDROID_API
    &ExportAndroidInputBindingsNew,
    &ExportAndroidJNIBindingsNew,
#endif

#if PLATFORM_WIN
    &ExportSpeechBindingsNew,
#endif
#if UNITY_EDITOR || PLATFORM_STANDALONE
    &ExportWindowsCrashReportingBindingsNew,
#endif
#if UNITY_METRO_API
    &ExportAppTrialBindingsNew,
    &ExportWindowsFileBindingsNew,
    &ExportWindowsDirectoryBindingsNew,
    &ExportWindowsCryptoBindingsNew,
    &ExportWSAApplicationBindingsNew,
    &ExportWSACursorBindingsNew,
    &ExportWSATilesBindingsNew,
    &ExportWSALauncherBindingsNew,
#endif

    &ExportSceneBindingsNew,
    &ExportSceneManagerBindingsNew,
    &ExportDrivenPropertyManagerBindingsNew,
    &ExportSceneUtilityBindingsNew,
    &ExportProfilerBindingsNew,
    &ExportProfilerMarkerBindingsNew,
    &ExportSamplerBindingsNew,
    &ExportRecorderBindingsNew,
// m1 code
    &ExportUnityStats2Bindings,
    &ExportUnityM1ExtensionBindings,
#if UNITY_EDITOR
    &ExportMemorySnapshotFileWriterBindingsNew,
    &ExportActiveEditorTrackerBindingsNew,
    &ExportEditorConnectionInternalBindings,
    &ExportLocalizationDatabaseBindingsNew,
    &ExportEditorUtilityBindingsNew,
    &ExportDragAndDropBindingsNew,
    &ExportHelpBindingsNew,
    &ExportMenuBindingsNew,
    &ExportSelectionBindingsNew,
    &ExportEditorPrefsBindingsNew,
    &ExportEditorAssembliesBindingsNew,
    &ExportUnsupportedBindingsNew,
    &ExportEditorUserBuildSettingsBindingsNew,
    &ExportEditorBuildSettingsBindingsNew,
    &ExportHandlesBindingsNew,
    &ExportHandleUtilityBindingsNew,
    &ExportEditorGUIUtilityBindingsNew,
    &ExportObjectNamesBindingsNew,
    &ExportUnityStatsBindings,
    &ExportMonoScriptBindingsNew,
    &ExportAsyncProgressBarBindingsNew,
    &ExportAnimationCurvePreviewCacheBindingsNew,
    &ExportGradientPreviewCacheBindingsNew,
    &ExportUsabilityAnalyticsBindingsNew,
    &ExportOSColorPickerBindingsNew,
    &ExportSavedGUIStateBindingsNew,
    &ExportGUIViewDebuggerHelperBindingsNew,
    &ExportInternalUtilityBindings,
    &ExportIHVImageFormatImporterBindingsNew,
    &ExportStaticOcclusionCullingBindingsNew,
    &ExportUnwrappingBindingsNew,
    &ExportTerrainInspectorUtilBindingsNew,
    &ExportOSUtilBindingsNew,
    &ExportInternalMeshUtilBindingsNew,
    &ExportVideoUtilBindingsNew,
    &ExportModuleMetadataBindings,
    &ExportLogEntriesBindingsNew,
    &ExportUnityTypeBindingsNew,
    &ExportWebURLsBindingsNew,
    &ExportAudioImporterBindingsNew,
    &ExportVideoImporterBindingsNew,
    &ExportModelImporterBindingsNew,
    &ExportMonoImporterBindingsNew,
    &ExportMovieImporterBindingsNew,
    &ExportPlayerSettingsSplashScreenEditorBindingsNew,
    &ExportPlayerSettingsSplashScreenBindingsNew,
    &ExportShaderImporterBindingsNew,
    &ExportTextureImporterBindingsNew,
    &ExportBumpMapSettingsBindingsNew,
    &ExportTextureUtilBindingsNew,
    &ExportTextureImporterTypesBindingsNew,
    &ExportChangeTrackerHandleBindingsNew,
    &ExportMediaEncoderBindingsNew,
    &ExportGameObjectRecorderBindingsNew,
    &ExportPrefabImporterBindingsNew,
    &ExportCompilationPipelineBindingsNew,
    &ExportVCProviderBindingsNew,
    &ExportVCMessageBindingsNew,
    &ExportVCCustomCommandBindingsNew,
    &ExportVCPluginBindingsNew,
    &ExportVCTaskBindingsNew,
    &ExportVCAssetBindingsNew,
    &ExportVCConflictItemBindingsNew,
    &ExportVCMergeResultBindingsNew,
    &ExportVCChangeSetBindingsNew,
    &ExportObjectFactoryBindingsNew,
    &ExportPlayablesBindingsNew,
    &ExportSpriteEditorExtensionBindingsNew,
    &ExportTextureGeneratorBindingsNew,
    &ExportAssetsMenuUtilityBindingsNew,
    &ExportStageUtilityBindingsNew,
    &ExportIconUtilityBindingsNew,
    &ExportTagManagerBindingsNew,
    &ExportPerformanceBindingsNew,
    &ExportBurstCompilerServiceBindingsNew,
#if INCLUDE_GI
    &ExportLightmappingBindingsNew,
#endif
#if INCLUDE_GI && INCLUDE_DYNAMIC_GI
    &ExportLightmapParametersBindingsNew,
#endif
    &ExportPluginImporterBindingsNew,
    &ExportShaderUtilBindings,
    &ExportShaderUtilBindingsNew,
    &ExportShaderKeywordBindingsNew,
    &ExportMeshUtilityBindingsNew,
    &ExportPrefabUtilityBindingsNew,
    &ExportEditorApplicationBindingsNew,
    &ExportEditorResourcesBindingsNew,
    &ExportBuildPipelineBindingsNew,
    &ExportSerializedPropertyBindingsNew,
    &ExportSerializedObjectBindingsNew,
    &ExportSerializedObjectChangeTrackerBindingsNew,
    &ExportAssetDatabaseBindings,
    &ExportAssetDatabaseBindingsNew,
    &ExportInternalEditorUtilityBindingsNew,
    &ExportEditorMaterialUtilityBindingsNew,
    &ExportFileUtilBindingsNew,
    &ExportAnimationUtilityBindingsNew,
    &ExportAnimationModeBindingsNew,
    &ExportStateMachineBindings,
    &ExportStateMachineBindingsNew,
    &ExportMuscleClipUtilityBindingsNew,
    &ExportAnimatorControllerBindingsNew,
    &ExportStateMachineBehaviourContextBindingsNew,
    &ExportAnimatorControllerLayerBindingsNew,
    &ExportBlendTreeBindingsNew,
    &ExportAvatarUtilityBindingsNew,
    &ExportBlendTreePreviewUtilityBindingsNew,
    &ExportPackageUtilityBindingsNew,
    &ExportEditorWindowBindingsNew,
    &ExportGUIViewBindingsNew,
    &ExportContainerWindowBindingsNew,
    &ExportWebViewBindings,
    &ExportAssetStoreUtilsBindings,
    &ExportAssetStoreToolUtilsBindings,
    &ExportProfilerAPIBindings,
    &ExportEditorSettingsBindingsNew,
    &ExportProfilerFrameDataViewBindingsNew,
    &ExportEditorUserSettingsBindingsNew,
    &ExportLightmapEditorSettingsBindingsNew,
    &ExportPlayerSettingsBindingsNew,
    &ExportPlayerSettingsAndroidBindingsNew,
    &ExportPlayerSettingsPlatformIconsBindingsNew,
    &ExportPlayerSettingsFacebookBindingsNew,
    &ExportPlayerSettingsIOSBindingsNew,
    &ExportPlayerSettingsTVOSBindingsNew,
    &ExportPlayerSettingsMacOSBindingsNew,
    &ExportPlayerSettingsLuminBindings,
    &ExportPlayerSettingsPS4BindingsNew,
    &ExportPlayerSettingsWSABindingsNew,
    &ExportPlayerSettingsXboxOneBindingsNew,
    &ExportPlayerSettingsWebGLBindings,
    &ExportPlayerSettingsSwitchBindingsNew,
    &ExportPlayerSettingsVRGoogleBindings,
    &ExportPlayerSettingsVulkanBindingsNew,
    &ExportRuntimeInitializeOnLoadManagerBindingsNew,
    &ExportAnnotationUtilityBindingsNew,
    &ExportLODUtilityBindings,
    &ExportRenderDocBindingsNew,
    &ExportGameObjectUtilityBindingsNew,
    &ExportComponentUtilityBindingsNew,
    &ExportAsyncHTTPClientBindingsNew,
    &ExportParticleSystemEditorBindingsNew,
    &ExportGUIDBindingsNew,
    &ExportAssetStoreContextBindings,
    &ExportUndoBindingsNew,
    &ExportAssetImportContextBindingsNew,
    &ExportAssetImporterBindingsNew,
    &ExportNativeFormatImporterUtilityBindingsNew,
    &ExportAssetPreviewBindingsNew,
    &ExportAudioUtilBindings,
    &ExportAudioMixerControllerBindings,
    &ExportAudioMixerGroupControllerBindings,
    &ExportAudioMixerEffectControllerBindings,
    &ExportAudioMixerSnapshotControllerBindings,
    &ExportAudioMixerDescriptionBindings,
    &ExportWaveformStreamerBindingsNew,
    &ExportAudioRendererBindingsNew,
    &ExportEditorBindingsNew,
    &ExportSpritePackerBindingsNew,
    &ExportSpritesEditorBindings,
    &ExportEditorSpriteAtlasBindingsNew,
    &ExportPolygonEditorBindingsNew,
    &ExportHighlighterBindingsNew,
    &ExportRegistryUtilBindingsNew,
    &ExportVisualStudioUtilBindingsNew,
    &ExportHardwareBindings,
    &ExportFrameDebuggerBindings,
    &ExportSpeedTreeImporterBindingsNew,
    &ExportDefaultAssetBindingsNew,
    &ExportAssetImportInProgressProxyBindingsNew,
#if ENABLE_CLOUD_SERVICES_COLLAB
    &ExportCollabBindingsNew,
#endif
    &ExportAPIUpdaterManagerBindingsNew,
    &ExportEditorSceneManagerBindingsNew,
    &ExportEditorGraphicsSettingsBindingsNew,
    &ExportDrivenPropertyManagerInternalBindingsNew,
    &ExportHomeWindowBindingsNew,

#if ENABLE_CLOUD_SERVICES
    &ExportUnityConnectBindingsNew,
    &ExportEditorProjectAccessBindingsNew,
#endif
#if ENABLE_CLOUD_SERVICES_ADS
    &ExportAdvertisementSettingsBindingsNew,
#endif
#if ENABLE_CLOUD_SERVICES_ANALYTICS
    &ExportAnalyticsSettingsBindingsNew,
#endif
#if ENABLE_CLOUD_SERVICES_PURCHASING
    &ExportPurchasingSettingsBindingsNew,
#endif
#if ENABLE_CLOUD_SERVICES_CRASH_REPORTING
    &ExportCrashReportingSettingsBindingsNew,
#endif
#if ENABLE_CLOUD_SERVICES_ANALYTICS
    &ExportPerformanceReportingSettingsBindingsNew,
#endif
#endif
    &ExportPlayerLoopBindingsNew,
    &ExportUnsafeUtilityBindingsNew,
    &ExportAtomicSafetyHandleBindingsNew,
    &ExportRenderPassAttachmentBindingsNew,
    &ExportScriptableRenderContextBindingsNew,
    &ExportRenderingCommandBufferBindingsNew,
    &ExportDiagnosticsUtilsBindingsNew,
    &ExportMemoryProfilingBindingsNew,
    &ExportAsyncReadManagerBindingsNew,
};

void RegisterAllInternalCalls()
{
    for (size_t i = 0; i < sizeof(sMonoBindingsRegistration) / sizeof(sMonoBindingsRegistration[0]); ++i)
        sMonoBindingsRegistration[i]();

    ModuleManager::Get().InvokeRegisterICalls();
}

#endif
