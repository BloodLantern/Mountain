// ReSharper disable CppNoDiscardExpression
#include "Common.hpp"

#include <Mountain/Utils/TimeSpan.hpp>

TEST(Utils_TimeSpan, Constants)
{
    EXPECT_EQ(TimeSpan::Zero().GetTicks(), 0);
    EXPECT_EQ(TimeSpan::FromTicks(100).GetTicks(), 100);
}

TEST(Utils_TimeSpan, FactoryMethods)
{
    EXPECT_EQ(TimeSpan::FromSeconds(1).GetTicks(), TimeSpan::TicksPerSecond);
    EXPECT_EQ(TimeSpan::FromMilliseconds(1).GetTicks(), TimeSpan::TicksPerMillisecond);
    EXPECT_EQ(TimeSpan::FromMinutes(1).GetTicks(), TimeSpan::TicksPerMinute);
    EXPECT_EQ(TimeSpan::FromHours(1).GetTicks(), TimeSpan::TicksPerHour);
    EXPECT_EQ(TimeSpan::FromDays(1).GetTicks(), TimeSpan::TicksPerDay);
}

TEST(Utils_TimeSpan, Properties)
{
    constexpr TimeSpan ts(1, 2, 3, 4, 5, 6); // 1d, 2h, 3m, 4s, 5ms, 6us

    EXPECT_EQ(ts.GetDays(), 1);
    EXPECT_EQ(ts.GetHours(), 2);
    EXPECT_EQ(ts.GetMinutes(), 3);
    EXPECT_EQ(ts.GetSeconds(), 4);
    EXPECT_EQ(ts.GetMilliseconds(), 5);
    EXPECT_EQ(ts.GetMicroseconds(), 6);

    EXPECT_DOUBLE_EQ(TimeSpan::FromHours(1.5).GetTotalMinutes(), 90.0);
}

TEST(Utils_TimeSpan, Nanoseconds)
{
    constexpr TimeSpan ts = TimeSpan::FromTicks(1); // 1 tick = 100ns
    EXPECT_EQ(ts.GetNanoseconds(), 100);
    EXPECT_DOUBLE_EQ(ts.GetTotalNanoseconds(), 100.0);
}

TEST(Utils_TimeSpan, Chrono)
{
    const TimeSpan ts = TimeSpan::FromMilliseconds(100);
    const auto chrono = ts.ToChrono();
    EXPECT_EQ(chrono.count(), 100'000'000); // 100ms in ns
}

TEST(Utils_TimeSpan, Duration)
{
    EXPECT_EQ(TimeSpan::FromSeconds(-5).Duration(), TimeSpan::FromSeconds(5));
    EXPECT_EQ(TimeSpan::FromSeconds(5).Duration(), TimeSpan::FromSeconds(5));
}

TEST(Utils_TimeSpan, Arithmetic)
{
    const TimeSpan a = TimeSpan::FromSeconds(10);
    const TimeSpan b = TimeSpan::FromSeconds(5);

    EXPECT_EQ((a + b).GetTotalSeconds(), 15.0);
    EXPECT_EQ((a - b).GetTotalSeconds(), 5.0);
    EXPECT_EQ((a * 2.0).GetTotalSeconds(), 20.0);
    EXPECT_EQ((2.0 * a).GetTotalSeconds(), 20.0);
    EXPECT_EQ((a / 2.0).GetTotalSeconds(), 5.0);
    EXPECT_DOUBLE_EQ(a / b, 2.0);
}

TEST(Utils_TimeSpan, ToString)
{
    EXPECT_EQ(TimeSpan(1, 2, 3).ToString(), "01:02:03");
    EXPECT_EQ(TimeSpan(1, 0, 0, 0).ToString(), "1.00:00:00");
    EXPECT_EQ(TimeSpan::FromMilliseconds(500).ToString(), "00:00:00.5000000");

    // Negative
    EXPECT_EQ(TimeSpan::FromHours(-1).ToString(), "-01:00:00");
    EXPECT_EQ(TimeSpan(-1, -2, -3, -4).ToString(), "-1.02:03:04");

    // Ticks (100ns precision)
    EXPECT_EQ(TimeSpan::FromTicks(1).ToString(), "00:00:00.0000001");
    EXPECT_EQ(TimeSpan::FromTicks(10).ToString(), "00:00:00.0000010");
    EXPECT_EQ(TimeSpan::FromTicks(10000000).ToString(), "00:00:01");

    // MinValue
    EXPECT_EQ(TimeSpan::MinValue().ToString(), "-10675199.02:48:05.4775808");
}

TEST(Utils_TimeSpan, Exceptions)
{
    EXPECT_THROW(TimeSpan::FromSeconds(std::numeric_limits<double_t>::quiet_NaN()), ArgumentException);
    EXPECT_THROW(-TimeSpan::MinValue(), OverflowException);
}

TEST(Utils_TimeSpan, Comparison)
{
    const TimeSpan a = TimeSpan::FromSeconds(10);
    const TimeSpan b = TimeSpan::FromSeconds(5);
    const TimeSpan c = TimeSpan::FromSeconds(10);

    EXPECT_TRUE(a > b);
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(a <= c);
    EXPECT_NE(a, b);
}

TEST(Utils_TimeSpan, TotalComponents)
{
    const TimeSpan ts = TimeSpan::FromHours(25.5); // 1d 1h 30m

    EXPECT_DOUBLE_EQ(ts.GetTotalDays(), 1.0625);
    EXPECT_DOUBLE_EQ(ts.GetTotalHours(), 25.5);
    EXPECT_DOUBLE_EQ(ts.GetTotalMinutes(), 1530.0);
    EXPECT_DOUBLE_EQ(ts.GetTotalSeconds(), 91800.0);
}
