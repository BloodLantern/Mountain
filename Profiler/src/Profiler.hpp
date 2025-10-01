#pragma once

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the PROFILER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// PROFILER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PROFILER_EXPORTS
#define PROFILER_API __declspec(dllexport)
#else
#define PROFILER_API __declspec(dllimport)
#endif

#ifdef PROFILING
	#define TRACY_IMPORTS
	#define TRACY_ENABLE
	#define TRACY_NO_EXIT
	#pragma comment(lib, "Profiler.lib")
#endif // PROFILING

#include "tracy/Tracy.hpp"

#ifdef __glad_h_

#endif // __glad_h_
