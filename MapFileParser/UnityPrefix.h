#ifndef UNITY_PREFIX_H
#define UNITY_PREFIX_H

#include <string>
#include <vector>
#include <set>
#include <map>

#if defined(__APPLE__)
    #include "Projects/PrecompiledHeaders/OSXPrefix.h"
#endif


// These are needed for prefix configure
#define UNITY_EXTERNAL_TOOL 1
// This has to be included before defining platform macros.
#include "Configuration/PrefixConfigure.h"

#ifdef _DEBUG
#if defined(ENABLE_UNIT_TESTS)
#undef ENABLE_UNIT_TESTS
#endif
#define ENABLE_UNIT_TESTS 1
#endif

#include "Runtime/Logging/LogAssert.h"

#endif
