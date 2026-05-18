#include "Mountain/Platform/Platform.hpp"

#ifdef ENVIRONMENT_LINUX
#include "Mountain/Platform/Linux/Linux.hpp"
#else
#include "Mountain/Platform/Windows/Windows.hpp"
#endif

using namespace Mountain;

bool Platform::Sleep(const TimeSpan duration)
{
#ifdef ENVIRONMENT_LINUX
    return Linux::Sleep(duration);
#else
    return Windows::Sleep(duration);
#endif
}

Guid Platform::NewGuid()
{
#ifdef ENVIRONMENT_LINUX
    return Linux::NewGuid();
#else
    return Windows::NewGuid();
#endif
}

void Platform::Cleanup()
{
#ifdef ENVIRONMENT_LINUX
    return Linux::Cleanup();
#else
    return Windows::Cleanup();
#endif
}
