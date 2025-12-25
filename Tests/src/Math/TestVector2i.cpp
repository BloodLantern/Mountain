#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Vector2i Zero = Vector2i::Zero();
constexpr Vector2i UnitX = Vector2i::UnitX();
constexpr Vector2i UnitY = Vector2i::UnitY();

constexpr Vector2i X4(4, 0);
constexpr Vector2i Y4(0, 4);

TEST(Vector2i, Constants)
{
    EXPECT_TRUE(Calc::Equals(Vector2i::Zero(), Vector2i()));

    EXPECT_TRUE(Calc::Equals(UnitX, Vector2i(1, 0)));
    EXPECT_TRUE(Calc::Equals(UnitY, Vector2i(0, 1)));
}

TEST(Vector2i, LengthAndNormalization)
{
    EXPECT_EQ(X4.SquaredLength(), 16);
    EXPECT_EQ(Y4.Length(), 4);

    EXPECT_EQ(Zero.SquaredLength(), 0);
    EXPECT_EQ(Zero.Length(), 0);
}

TEST(Vector2i, DotProduct)
{
    EXPECT_EQ(Vector2i::Dot(UnitX, UnitY), 0.f);
    EXPECT_EQ(Vector2i::Dot(UnitX, UnitX), 1.f);
    EXPECT_EQ(Vector2i::Dot(UnitX, -UnitX), -1.f);
}

TEST(Vector2i, CrossProduct)
{
    EXPECT_EQ(Vector2i::Cross(UnitX, UnitY), 1.f);
    EXPECT_EQ(Vector2i::Cross(UnitY, UnitX), -1.f);
}

TEST(Vector2i, SubscriptOutOfRangeThrow)
{
    EXPECT_THROW((void) UnitX[2], std::out_of_range);
}

TEST(Vector2i, Operators)
{
    EXPECT_TRUE(Calc::Equals(UnitX + UnitY, Vector2i(1)));
    EXPECT_TRUE(Calc::Equals(UnitX - UnitX, Vector2i(0)));

    EXPECT_TRUE(Calc::Equals(UnitX * 2, Vector2i(2, 0)));
    EXPECT_TRUE(Calc::Equals(Vector2i(1) * Vector2i(2, 0), Vector2i(2, 0)));

    Vector2i temp = UnitX;
    EXPECT_TRUE(Calc::Equals(temp += UnitY, Vector2i(1)));
    EXPECT_TRUE(Calc::Equals(temp -= UnitX, UnitY));

    temp = Vector2i(1);
    EXPECT_TRUE(Calc::Equals(temp *= 2, Vector2i(2)));
    EXPECT_TRUE(Calc::Equals(temp *= Vector2i(2, 0), Vector2i(4, 0)));

    temp = Vector2i(10, 20);
    EXPECT_TRUE(Calc::Equals(temp /= 2, Vector2i(5, 10)));
}

TEST(Vector2i, Formatting)
{
    EXPECT_EQ(std::format("{0:02d}", UnitX), "01 ; 00");
}
