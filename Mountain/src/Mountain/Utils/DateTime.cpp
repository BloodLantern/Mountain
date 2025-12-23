

#include "Mountain/Utils/DateTime.hpp"

#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

DateTime DateTime::Now()
{
    static s64 utcOffsetTicks = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::current_zone()->get_info(std::chrono::system_clock::now()).offset).count() / 100;

    const s64 ticks = UtcNow().GetTicks() + utcOffsetTicks;
    if (static_cast<u64>(ticks) <= MaxTicks)
        return DateTime{static_cast<u64>(ticks) | KindLocal};
    return DateTime{ticks < 0 ? KindLocal : MaxTicks | KindLocal};
}

DateTime DateTime::UtcNow()
{
    u64 fileTime; // mark only the temp local as address-taken
    GetSystemTimeAsFileTime(reinterpret_cast<LPFILETIME>(&fileTime));

    return DateTime{(fileTime + (FileTimeOffset | KindUtc))};
}

DateTime DateTime::Today()
{
    return Now().GetDate();
}

std::string DateTime::ToString() const
{
    return std::format(
        "{:04}/{:02}/{:02} {:02}:{:02}:{:02}",
        GetYear(),
        GetMonth(),
        GetDay(),
        GetHour(),
        GetMinute(),
        GetSecond()
    );
}
