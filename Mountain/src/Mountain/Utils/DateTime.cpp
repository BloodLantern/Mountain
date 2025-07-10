#include "Mountain/Utils/DateTime.hpp"

using namespace Mountain;

DateTime DateTime::Now()
{
    THROW(NotImplementedException{});
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
