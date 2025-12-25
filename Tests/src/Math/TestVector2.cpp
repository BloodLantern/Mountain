#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Vector2 Zero = Vector2::Zero();
constexpr Vector2 UnitX = Vector2::UnitX();
constexpr Vector2 UnitY = Vector2::UnitY();

TEST(Vector2, Constants)
{
    EXPECT_TRUE(Calc::Equals(Zero, Vector2()));

    EXPECT_TRUE(Calc::Equals(UnitX, Vector2(1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitY, Vector2(0.f, 1.f)));
}

constexpr Vector2 X4(4.f, 0.f);
constexpr Vector2 Y4(0.f, 4.f);

TEST(Vector2, LengthAndNormalization)
{
    EXPECT_EQ(X4.SquaredLength(), 16.f);
    EXPECT_EQ(Y4.Length(), 4.f);

    EXPECT_EQ(Zero.SquaredLength(), 0.f);
    EXPECT_EQ(Zero.Length(), 0.f);

    EXPECT_EQ(X4.Normalized().SquaredLength(), 1.f);
    EXPECT_EQ(Y4.Normalized().Length(), 1.f);
}

TEST(Vector2, Normal)
{
    EXPECT_TRUE(Calc::Equals(UnitX.Normal(), UnitY) || Calc::Equals(UnitX.Normal(), -UnitY));
    EXPECT_TRUE(Calc::Equals(UnitY.Normal(), UnitX) || Calc::Equals(UnitY.Normal(), -UnitX));
}

TEST(Vector2, DotProduct)
{
    EXPECT_EQ(Vector2::Dot(UnitX, UnitY), 0.f);
    EXPECT_EQ(Vector2::Dot(UnitX, UnitX), 1.f);
    EXPECT_EQ(Vector2::Dot(UnitX, -UnitX), -1.f);
}

TEST(Vector2, CrossProduct)
{
    EXPECT_EQ(Vector2::Cross(UnitX, UnitY), 1.f);
    EXPECT_EQ(Vector2::Cross(UnitY, UnitX), -1.f);
}

TEST(Vector2, Lerp)
{
    EXPECT_TRUE(Calc::Equals(Calc::Lerp(Vector2::Zero(), Vector2(1.f), 0.5f), Vector2(0.5f)));
}

TEST(Vector2, SubscriptOutOfRangeThrow)
{
    EXPECT_THROW((void) UnitX[2], std::out_of_range);
}

TEST(Vector2, Checks)
{
    EXPECT_TRUE((Vector2(1.f) / 0.f).IsInfinity());
    EXPECT_TRUE((-(Vector2(-1.f) / 0.f)).IsInfinity());
    EXPECT_TRUE((Zero / 0.f).IsNaN());
}

TEST(Vector2, Operators)
{
    EXPECT_TRUE(Calc::Equals(UnitX + UnitY, Vector2(1.f)));
    EXPECT_TRUE(Calc::Equals(UnitX - UnitX, Vector2(0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX * 2.f, Vector2(2.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector2(1.f) * Vector2(2.f, 0.5f), Vector2(2.f, 0.5f)));

    EXPECT_TRUE(Calc::Equals(UnitX / 2.f, Vector2(0.5f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector2(1.f) / Vector2(2.f, 0.5f), Vector2(0.5f, 2.f)));

    Vector2 temp = UnitX;
    EXPECT_TRUE(Calc::Equals(temp += UnitY, Vector2(1.f)));
    EXPECT_TRUE(Calc::Equals(temp -= UnitX, UnitY));

    temp = Vector2(1.f);
    EXPECT_TRUE(Calc::Equals(temp *= 2.f, Vector2(2.f)));
    EXPECT_TRUE(Calc::Equals(temp *= Vector2(2.f, 0.5f), Vector2(4.f, 1.f)));

    EXPECT_TRUE(Calc::Equals(temp /= 2.f, Vector2(2.f, 0.5f)));
    EXPECT_TRUE(Calc::Equals(temp /= Vector2(2.f, 0.5f), Vector2(1.f)));
}

TEST(Vector2, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", UnitX), "01.000 ; 00.000");
}
