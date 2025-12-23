#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Vector3 Zero = Vector3::Zero();
constexpr Vector3 UnitX = Vector3::UnitX();
constexpr Vector3 UnitY = Vector3::UnitY();
constexpr Vector3 UnitZ = Vector3::UnitZ();

constexpr Vector3 X4(4.f, 0.f, 0.f);
constexpr Vector3 Y4(0.f, 4.f, 0.f);

TEST(Vector3, Constants)
{
    EXPECT_TRUE(Calc::Equals(Vector3::Zero(), Vector3()));

    EXPECT_TRUE(Calc::Equals(UnitX, Vector3(1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitY, Vector3(0.f, 1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitZ, Vector3(0.f, 0.f, 1.f)));
}

TEST(Vector3, LengthAndNormalization)
{
    EXPECT_EQ(X4.SquaredLength(), 16.f);
    EXPECT_EQ(Y4.Length(), 4.f);

    EXPECT_EQ(Zero.SquaredLength(), 0.f);
    EXPECT_EQ(Zero.Length(), 0.f);

    EXPECT_EQ(X4.Normalized().SquaredLength(), 1.f);
    EXPECT_EQ(Y4.Normalized().Length(), 1.f);

    EXPECT_NEAR(UnitX.Rescaled(5.f).Length(), 5.f, 0.0001f);
}

TEST(Vector3, Combine)
{
    EXPECT_TRUE(Calc::Equals(Vector3::Combine(UnitX, UnitY, 2.f, 3.f), Vector3(2.f, 3.f, 0.f)));
}

TEST(Vector3, DotProduct)
{
    EXPECT_EQ(Vector3::Dot(UnitX, UnitY), 0.f);
    EXPECT_EQ(Vector3::Dot(UnitX, UnitX), 1.f);
    EXPECT_EQ(Vector3::Dot(UnitX, -UnitX), -1.f);
}

TEST(Vector3, CrossProduct)
{
    EXPECT_TRUE(Calc::Equals(Vector3::Cross(UnitX, UnitY), UnitZ));
    EXPECT_TRUE(Calc::Equals(Vector3::Cross(UnitY, UnitZ), UnitX));
    EXPECT_TRUE(Calc::Equals(Vector3::Cross(UnitZ, UnitX), UnitY));
}

TEST(Vector3, Lerp)
{
    EXPECT_TRUE(Calc::Equals(Calc::Lerp(Vector3::Zero(), Vector3(1.f), 0.5f), Vector3(0.5f)));
}

TEST(Vector3, SubscriptOutOfRangeThrow)
{
    EXPECT_THROW((void) UnitX[3], std::out_of_range);
}

TEST(Vector3, Checks)
{
    EXPECT_TRUE((Vector3(1.f) / 0.f).IsInfinity());
    EXPECT_TRUE((-(Vector3(-1.f) / 0.f)).IsInfinity());
    EXPECT_TRUE((Zero / 0.f).IsNaN());
}

TEST(Vector3, Operators)
{
    EXPECT_TRUE(Calc::Equals(UnitX + UnitY, Vector3(1.f, 1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitX - UnitX, Vector3(0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX * 2.f, Vector3(2.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector3(1.f) * Vector3(2.f, 0.5f, 0.f), Vector3(2.f, 0.5f, 0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX / 2.f, Vector3(0.5f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Vector3(1.f) / Vector3(2.f, 0.5f, 1.f), Vector3(0.5f, 2.f, 1.f)));

    Vector3 temp = UnitX;
    EXPECT_TRUE(Calc::Equals(temp += UnitY, Vector3(1.f, 1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(temp -= UnitX, UnitY));

    temp = Vector3(1.f);
    EXPECT_TRUE(Calc::Equals(temp *= 2.f, Vector3(2.f)));
    EXPECT_TRUE(Calc::Equals(temp *= Vector3(2.f, 0.5f, 0.f), Vector3(4.f, 1.f, 0.f)));

    EXPECT_TRUE(Calc::Equals(temp /= 2.f, Vector3(2.f, 0.5f, 0.f)));
    EXPECT_TRUE(Calc::Equals(temp /= Vector3(2.f, 0.5f, 1.f), Vector3(1.f, 1.f, 0.f)));
}

TEST(Vector3, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", UnitX), "01.000 ; 00.000 ; 00.000");
}
