#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

TEST(calc, Sign)
{
    EXPECT_EQ(Calc::Sign(17.8f), 1.f);
    EXPECT_EQ(Calc::Sign(-86.1f), -1.f);
    EXPECT_EQ(Calc::Sign(0.f), 0.f);
}

TEST(calc, Abs)
{
    EXPECT_EQ(Calc::Abs(17.8f), 17.8f);
    EXPECT_EQ(Calc::Abs(-86.1f), 86.1f);
    EXPECT_EQ(Calc::Abs(0.f), 0.f);
}

TEST(calc, IsZero)
{
    EXPECT_TRUE(Calc::IsZero(Calc::Zero));
    EXPECT_TRUE(Calc::IsZero(0.000001f));
}

TEST(calc, Equals)
{
    EXPECT_TRUE(Calc::Equals(1.f, 1.00000075f));
    EXPECT_FALSE(Calc::Equals(1.f, 1.0000075f));
}

TEST(calc, Clamp)
{
    EXPECT_EQ(Calc::Clamp(5.f, 0.f, 10.f), 5.f);
    EXPECT_EQ(Calc::Clamp(-5.f, 0.f, 10.f), 0.f);
    EXPECT_EQ(Calc::Clamp(15.f, 0.f, 10.f), 10.f);
}

TEST(calc, Lerp)
{
    EXPECT_EQ(Calc::Lerp(0.f, 10.f, 0.5f), 5.f);
    EXPECT_EQ(Calc::Lerp(0.f, 10.f, 0.f), 0.f);
    EXPECT_EQ(Calc::Lerp(0.f, 10.f, 1.f), 10.f);
}

TEST(calc, RoundFloorCeil)
{
    EXPECT_EQ(Calc::Round(1.4f), 1.f);
    EXPECT_EQ(Calc::Round(1.6f), 2.f);
    EXPECT_EQ(Calc::Floor(1.9f), 1.f);
    EXPECT_EQ(Calc::Ceil(1.1f), 2.f);
}

TEST(calc, YoYo)
{
    EXPECT_EQ(Calc::YoYo(0.f), 0.f);
    EXPECT_EQ(Calc::YoYo(0.25f), 0.5f);
    EXPECT_EQ(Calc::YoYo(0.5f), 1.f);
    EXPECT_EQ(Calc::YoYo(0.75f), 0.5f);
    EXPECT_EQ(Calc::YoYo(1.f), 0.f);
}

TEST(calc, ClampedMap)
{
    EXPECT_EQ(Calc::ClampedMap(5.f, 0.f, 10.f, 0.f, 100.f), 50.f);
    EXPECT_EQ(Calc::ClampedMap(-5.f, 0.f, 10.f, 0.f, 100.f), 0.f);
    EXPECT_EQ(Calc::ClampedMap(15.f, 0.f, 10.f, 0.f, 100.f), 100.f);
}

TEST(calc, OnInterval)
{
    EXPECT_TRUE(Calc::OnInterval(1.1f, 0.9f, 1.0f));
    EXPECT_FALSE(Calc::OnInterval(0.9f, 0.8f, 1.0f));
}
