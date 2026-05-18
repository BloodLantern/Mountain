#include "Mountain/Platform/Platform.hpp"

#ifdef ENVIRONMENT_LINUX

#include "Mountain/Platform/Linux/Linux.hpp"

#define PLATFORM_DEPENDENT_CALL(function, ...) Linux::function(__VA_ARGS__)

#else

#include "Mountain/Platform/Windows/Windows.hpp"

#define PLATFORM_DEPENDENT_CALL(function, ...) Windows::function(__VA_ARGS__)

#endif

using namespace Mountain;

bool Platform::Sleep(const TimeSpan duration) { return PLATFORM_DEPENDENT_CALL(Sleep, duration); }

Guid Platform::NewGuid() { return PLATFORM_DEPENDENT_CALL(NewGuid); }

DateTime Platform::UtcNow() { return PLATFORM_DEPENDENT_CALL(UtcNow); }

void Platform::Cleanup() { return PLATFORM_DEPENDENT_CALL(Cleanup); }
