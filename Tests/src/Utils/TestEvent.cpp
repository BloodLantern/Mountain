#include "PrecompiledHeader.hpp"

#include <Mountain/Utils/Event.hpp>

using namespace Mountain;

TEST(Utils_Event, BasicFlow)
{
    Event<int> onEvent;
    int callCount = 0;
    int lastValue = 0;

    auto callback = [&](int value)
    {
        callCount++;
        lastValue = value;
    };

    onEvent += callback;
    onEvent.Invoke(10);

    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(lastValue, 10);

    onEvent(20);
    EXPECT_EQ(callCount, 2);
    EXPECT_EQ(lastValue, 20);

    onEvent -= callback;
    onEvent.Invoke(30);
    EXPECT_EQ(callCount, 2); // Should not have increased
}

TEST(Utils_Event, MultipleSubscribers)
{
    Event<> onEvent;
    int count = 0;

    auto sub1 = [&]() { count++; };
    auto sub2 = [&]() { count += 2; };

    onEvent += sub1;
    onEvent += sub2;

    onEvent.Invoke();
    EXPECT_EQ(count, 3);

    onEvent -= sub1;
    onEvent.Invoke();
    EXPECT_EQ(count, 5);
}

TEST(Utils_Event, Clear)
{
    Event<int> onEvent;
    int count = 0;
    onEvent += [&](int) { count++; };

    onEvent.Invoke(1);
    EXPECT_EQ(count, 1);

    onEvent.Clear();
    onEvent.Invoke(1);
    EXPECT_EQ(count, 1);
}

namespace
{
    int g_StaticCallCount = 0;
    void StaticCallback(int) { g_StaticCallCount++; }
}

TEST(Utils_Event, StaticFunction)
{
    Event<int> onEvent;
    g_StaticCallCount = 0;

    onEvent += StaticCallback;
    onEvent.Invoke(1);
    EXPECT_EQ(g_StaticCallCount, 1);

    onEvent -= StaticCallback;
    onEvent.Invoke(1);
    EXPECT_EQ(g_StaticCallCount, 1);
}
