#include "Mountain/Core.hpp"

#include "Mountain/Utils/DateTime.hpp"

#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

DateTime DateTime::Now()
{
    const int64_t tick = UtcNow().GetTicks();
    if (static_cast<uint64_t>(tick) <= MaxTicks)
        return DateTime{static_cast<uint64_t>(tick) | KindLocal};
    return DateTime{tick < 0 ? KindLocal : MaxTicks | KindLocal};
}

DateTime DateTime::UtcNow()
{
    uint64_t fileTime; // mark only the temp local as address-taken
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
        "{}/{}/{} {}:{}:{}",
        GetYear(),
        GetMonth(),
        GetDay(),
        GetHour(),
        GetMinute(),
        GetSecond()
    );
}
