#include "Common.hpp"

#include <Mountain/Utils/DateTime.hpp>

// ReSharper disable once CppInconsistentNaming
class Utils_DateTime : public testing::Test
{
protected:
    DateTime time{2000, 7, 15, 12, 10, 2, 321, 123};
};

TEST_F(Utils_DateTime, Components)
{
    EXPECT_EQ(time.GetYear(), 2000);
    EXPECT_EQ(time.GetMonth(), 7);
    EXPECT_EQ(time.GetDay(), 15);
    EXPECT_EQ(time.GetHour(), 12);
    EXPECT_EQ(time.GetMinute(), 10);
    EXPECT_EQ(time.GetSecond(), 2);
    EXPECT_EQ(time.GetMillisecond(), 321);
    EXPECT_EQ(time.GetMicrosecond(), 123);

    EXPECT_EQ(time.GetDate(), (DateTime{2000, 7, 15}));
    EXPECT_EQ(time.GetTimeOfDay(), (TimeSpan{0, 12, 10, 2, 321, 123}));
    EXPECT_EQ(time.GetDayOfWeek(), DayOfWeek::Saturday);
    EXPECT_EQ(time.GetDayOfYear(), 197);

    EXPECT_EQ(time - time.GetTimeOfDay(), time.GetDate());
    EXPECT_EQ(time.GetDate() + time.GetTimeOfDay(), time);
}

TEST_F(Utils_DateTime, ToString)
{
    EXPECT_EQ(time.ToString(), "2000/07/15 12:10:02");
}

TEST_F(Utils_DateTime, HashCode)
{
    EXPECT_EQ(time.GetHashCode(), time.GetHashCode());
    EXPECT_NE(time.GetHashCode(), DateTime::Now().GetHashCode());
}
