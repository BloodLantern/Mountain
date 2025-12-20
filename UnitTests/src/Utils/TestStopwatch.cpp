#include "Common.hpp"

#include <thread>

#include <Mountain/Utils/Stopwatch.hpp>

TEST(Utils_Stopwatch, BasicFlow)
{
    Stopwatch sw;
    EXPECT_FALSE(sw.GetIsRunning());
    EXPECT_EQ(sw.GetElapsedTicks(), 0);

    sw.Start();
    EXPECT_TRUE(sw.GetIsRunning());

    std::this_thread::sleep_for(std::chrono::milliseconds{10});

    sw.Stop();
    EXPECT_FALSE(sw.GetIsRunning());
    EXPECT_GT(sw.GetElapsedMilliseconds(), 0);

    const double_t elapsed = sw.GetElapsedMilliseconds();
    sw.Reset();
    EXPECT_EQ(sw.GetElapsedTicks(), 0);
    EXPECT_FALSE(sw.GetIsRunning());
}

TEST(Utils_Stopwatch, StartNew)
{
    const Stopwatch sw = Stopwatch::StartNew();
    EXPECT_TRUE(sw.GetIsRunning());
}

TEST(Utils_Stopwatch, Restart)
{
    Stopwatch sw = Stopwatch::StartNew();
    std::this_thread::sleep_for(std::chrono::milliseconds{5});
    sw.Restart();

    // Elapsed should have been cleared, and it should still be running
    EXPECT_TRUE(sw.GetIsRunning());
    EXPECT_LT(sw.GetElapsedMilliseconds(), 2);
}

TEST(Utils_Stopwatch, StaticMethods)
{
    const int64_t ts1 = Stopwatch::GetTimestamp();
    std::this_thread::sleep_for(std::chrono::milliseconds{1});
    const int64_t ts2 = Stopwatch::GetTimestamp();

    EXPECT_GE(ts2, ts1);
    EXPECT_GT(Stopwatch::GetFrequency(), 0);

    const TimeSpan elapsed = Stopwatch::GetElapsedTime(ts1, ts2);
    EXPECT_GT(elapsed.GetTicks(), 0);
}
