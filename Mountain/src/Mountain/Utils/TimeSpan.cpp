#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/TimeSpan.hpp"

#include "Mountain/Exceptions/ThrowHelper.hpp"

using namespace Mountain;

std::string TimeSpan::ToString() const
{
    std::string result;

    const bool_t daysCheck = GetDays() > 0;
    const bool_t hoursCheck = GetHours() > 0;
    const bool_t minutesCheck = GetMinutes() > 0;

    if (daysCheck)
        result += std::format("{}.", GetDays());

    if (daysCheck || hoursCheck)
        result += std::format("{:02}:", GetHours());

    if (daysCheck || hoursCheck || minutesCheck)
        result += std::format("{:02}:", GetMinutes());

    result += std::format("{}", GetSeconds());

    const bool_t millisecondsCheck = GetMilliseconds() > 0;
    const bool_t microsecondsCheck = GetMicroseconds() > 0;
    const bool_t nanosecondsCheck = GetNanoseconds() > 0;

    if (nanosecondsCheck || microsecondsCheck)
        result += std::format(".{:03}", GetMilliseconds());
    else if (millisecondsCheck)
        result += std::format(".{}", GetMilliseconds());

    if (nanosecondsCheck || microsecondsCheck)
        result += std::format("{:03}", GetMicroseconds());
    else if (microsecondsCheck)
        result += std::format(".{}", GetMilliseconds());

    if (nanosecondsCheck)
        result += std::format("{}", GetNanoseconds());

    return result;
}
