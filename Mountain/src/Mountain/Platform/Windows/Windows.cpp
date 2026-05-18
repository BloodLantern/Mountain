#include "Mountain/Platform/Windows/Windows.hpp"

#ifdef ENVIRONMENT_WINDOWS

#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

namespace
{
    HANDLE waitableTimer = nullptr;

    bool WaitWaitableTimer(const TimeSpan timeSpan)
    {
        if (!waitableTimer)
            return false;

        const u64 ul = static_cast<u64>(-timeSpan.GetTicks());
        const FILETIME waitDuration{
            .dwLowDateTime = static_cast<DWORD>(ul & 0xFFFFFFFF),
            .dwHighDateTime = static_cast<DWORD>(ul >> 32)
        };

        if (SetWaitableTimerEx(waitableTimer, reinterpret_cast<const LARGE_INTEGER*>(&waitDuration), 0, nullptr, nullptr, nullptr, 0))
        {
            WaitForSingleObject(waitableTimer, INFINITE);
            Windows::CheckError();
            return true;
        }

        Windows::SilenceError();

        return false;
    }

    HANDLE GetWaitableTimer()
    {
        if (waitableTimer)
            return waitableTimer;

        // Attempt to create a high-resolution timer, only available since Windows 10, version 1803
        waitableTimer = CreateWaitableTimerEx(nullptr, nullptr, CREATE_WAITABLE_TIMER_MANUAL_RESET | CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);

        // Fall back to a more supported version if not available.
        // This is still far more accurate than std::this_thread::sleep_for.
        if (!waitableTimer)
            waitableTimer = CreateWaitableTimerEx(nullptr, nullptr, CREATE_WAITABLE_TIMER_MANUAL_RESET, TIMER_ALL_ACCESS);

        Windows::SilenceError();

        return waitableTimer;
    }
}

bool Windows::CheckError()
{
    const DWORD error = GetLastError();

    if (error != NOERROR)
    {
        LPVOID lpMsgBuf = nullptr;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&lpMsgBuf),
            0,
            nullptr
        );
        SilenceError();

        Logger::LogError("[Windows] Error {}: {}", error, static_cast<LPSTR>(lpMsgBuf));

        return true;
    }

    return false;
}

void Windows::SilenceError() { (void) GetLastError(); }

bool Windows::Sleep(const TimeSpan duration) { return WaitWaitableTimer(duration); }

void Windows::Cleanup()
{
    if (waitableTimer)
    {
        CloseHandle(waitableTimer);
        Windows::CheckError();
    }
}

std::string Windows::GetAppdataLocalPath()
{
    CHAR result[MAX_PATH]{};
    (void) SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, result);
    CheckError();
    return result;
}

std::string Windows::GetAppdataRoamingPath()
{
    CHAR result[MAX_PATH]{};
    (void) SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, result);
    CheckError();
    return result;
}

#endif
