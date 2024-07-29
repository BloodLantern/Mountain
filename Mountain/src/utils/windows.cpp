#include "utils/windows.hpp"

#include "utils/logger.hpp"

using namespace Mountain;

bool_t Windows::CheckError()
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
