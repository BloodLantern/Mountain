#include "Mountain/Platform/Linux/Linux.hpp"

#ifdef ENVIRONMENT_LINUX

using namespace Mountain;

constexpr int InterruptError = 4;

bool Linux::Sleep(const TimeSpan duration)
{
    constexpr int nanosecondsPerSecond = 1000 * 1000 * 1000;

    const s64 nanoseconds = static_cast<s64>(duration.GetTotalNanoseconds());

    timespec timeSpec
    {
        .tv_sec = nanoseconds / nanosecondsPerSecond,
        .tv_nsec = nanoseconds % nanosecondsPerSecond,
    };
    timespec remaining;

    int result;

    while ((result = nanosleep(&timeSpec, &remaining)) == -1 && errno == InterruptError)
    {
        // The pause can be interrupted by a signal that was delivered to the thread.
        // Sleep again with remaining time if it happened.
        timeSpec = remaining;
    }

    return result == 0; // Any errors other than InterruptError should return false.
}

void Linux::Cleanup()
{
}

#endif
