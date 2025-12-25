#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Vector4 Zero = Vector4::Zero();
constexpr Vector4 UnitX = Vector4::UnitX();
constexpr Vector4 UnitY = Vector4::UnitY();
constexpr Vector4 UnitZ = Vector4::UnitZ();
constexpr Vector4 UnitW = Vector4::UnitW();

constexpr Vector4 X4(4.f, 0.f, 0.f, 0.f);
constexpr Vector4 Y4(0.f, 4.f, 0.f, 0.f);

TEST(Vector4, Constants)
{
    EXPECT_TRUE(Calc::Equals(Vector4::Zero(), Vector4()));

    EXPECT_TRUE(Calc::Equals(UnitX, Vector4(1.f, 0.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitY, Vector4(0.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitZ, Vector4(0.f, 0.f, 1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitW, Vector4(0.f, 0.f, 0.f, 1.f)));
}

TEST(Vector4, LengthAndNormalization)
{
    EXPECT_EQ(X4.SquaredLength(), 16.f);
    EXPECT_EQ(Y4.Length(), 4.f);

    EXPECT_EQ(Zero.SquaredLength(), 0.f);
    EXPECT_EQ(Zero.Length(), 0.f);

    EXPECT_EQ(X4.Normalized().SquaredLength(), 1.f);
    EXPECT_EQ(Y4.Normalized().Length(), 1.f);
}

TEST(Vector4, DotProduct)
{
    EXPECT_EQ(Vector4::Dot(UnitX, UnitY), 0.f);
    EXPECT_EQ(Vector4::Dot(UnitX, UnitX), 1.f);
    EXPECT_EQ(Vector4::Dot(UnitX, -UnitX), -1.f);
}

TEST(Vector4, Lerp)
{
    EXPECT_TRUE(Calc::Equals(Calc::Lerp(Vector4::Zero(), Vector4(1.f), 0.5f), Vector4(0.5f)));
}

TEST(Vector4, SubscriptOutOfRangeThrow)
{
    EXPECT_THROW((void) UnitX[4], std::out_of_range);
}

TEST(Vector4, Checks)
{
    EXPECT_TRUE((Vector4(1.f) / 0.f).IsInfinity());
    EXPECT_TRUE((-(Vector4(-1.f) / 0.f)).IsInfinity());
    EXPECT_TRUE((Zero / 0.f).IsNaN());
}

TEST(Vector4, Operators)
{
    EXPECT_TRUE(Calc::Equals(UnitX + UnitY, Vector4(1.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitX - UnitX, Vector4(0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX * 2.f, Vector4(2.f, 0.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector4(1.f) * Vector4(2.f, 0.5f, 0.f, 0.f), Vector4(2.f, 0.5f, 0.f, 0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX / 2.f, Vector4(0.5f, 0.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector4(1.f) / Vector4(2.f, 0.5f, 1.f, 1.f), Vector4(0.5f, 2.f, 1.f, 1.f)));

    Vector4 temp = UnitX;
    EXPECT_TRUE(Calc::Equals(temp += UnitY, Vector4(1.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(temp -= UnitX, UnitY));

    temp = Vector4(1.f);
    EXPECT_TRUE(Calc::Equals(temp *= 2.f, Vector4(2.f)));
    EXPECT_TRUE(Calc::Equals(temp *= Vector4(2.f, 0.5f, 0.f, 0.f), Vector4(4.f, 1.f, 0.f, 0.f)));

    EXPECT_TRUE(Calc::Equals(temp /= 2.f, Vector4(2.f, 0.5f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(temp /= Vector4(2.f, 0.5f, 1.f, 1.f), Vector4(1.f, 1.f, 0.f, 0.f)));
}

TEST(Vector4, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", UnitX), "01.000 ; 00.000 ; 00.000 ; 00.000");
}
