#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Quaternion Zero = Quaternion::Zero();
constexpr Quaternion UnitX = Quaternion::UnitX();
constexpr Quaternion UnitY = Quaternion::UnitY();
constexpr Quaternion UnitZ = Quaternion::UnitZ();
constexpr Quaternion UnitW = Quaternion::UnitW();

constexpr Quaternion X4(4.f, 0.f, 0.f, 0.f);
constexpr Quaternion Y4(0.f, 4.f, 0.f, 0.f);

const Quaternion RotationHalfCircleZ = Quaternion::FromAxisAngle(Vector3::UnitZ(), Calc::PiOver2);
const Vector3 RotatedUnitX = Quaternion::Rotate(Vector3::UnitX(), RotationHalfCircleZ);

TEST(Quaternion, Constants)
{
    EXPECT_TRUE(Calc::Equals(Quaternion::Zero(), Quaternion()));

    EXPECT_TRUE(Calc::Equals(UnitX, Quaternion(1.f, 0.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitY, Quaternion(0.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitZ, Quaternion(0.f, 0.f, 1.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitW, Quaternion(0.f, 0.f, 0.f, 1.f)));

    EXPECT_TRUE(Calc::Equals(UnitW, Quaternion::Identity()));
}

TEST(Quaternion, LengthAndNormalization)
{
    EXPECT_EQ(X4.SquaredLength(), 16.f);
    EXPECT_EQ(Y4.Length(), 4.f);

    EXPECT_EQ(Zero.SquaredLength(), 0.f);
    EXPECT_EQ(Zero.Length(), 0.f);

    EXPECT_EQ(X4.Normalized().SquaredLength(), 1.f);
    EXPECT_EQ(Y4.Normalized().Length(), 1.f);
}

TEST(Quaternion, DotProduct)
{
    EXPECT_EQ(Quaternion::Dot(UnitX, UnitY), 0.f);
    EXPECT_EQ(Quaternion::Dot(UnitX, UnitX), 1.f);
    EXPECT_EQ(Quaternion::Dot(UnitX, -UnitX), -1.f);
}

TEST(Quaternion, Lerp)
{
    EXPECT_TRUE(Calc::Equals(Quaternion::Lerp(Quaternion::Zero(), Quaternion(1.f), 0.5f), Quaternion(0.5f)));
    EXPECT_TRUE(Calc::Equals(Quaternion::Slerp(Quaternion::Zero(), Quaternion(1.f), 0.5f), Quaternion(0.707107f)));
}

TEST(Quaternion, SubscriptOutOfRangeThrow)
{
    EXPECT_THROW((void) UnitX[4], std::out_of_range);
}

TEST(Quaternion, Checks)
{
    EXPECT_TRUE((Quaternion(1.f) / 0.f).IsInfinity());
    EXPECT_TRUE((-(Quaternion(-1.f) / 0.f)).IsInfinity());
    EXPECT_TRUE((Zero / 0.f).IsNaN());
}

TEST(Quaternion, Convertions)
{
    EXPECT_TRUE(Calc::Equals(Quaternion::ToEuler(RotationHalfCircleZ), Vector3(0.f, 0.f, Calc::PiOver2)));
}

TEST(Quaternion, Rotation)
{
    EXPECT_TRUE(Calc::Equals(RotatedUnitX, Vector3::UnitY()));

    EXPECT_TRUE(Calc::Equals(Quaternion(RotatedUnitX), RotationHalfCircleZ * Vector3::UnitX() * RotationHalfCircleZ.Conjugate()));

    EXPECT_TRUE(Calc::Equals(RotationHalfCircleZ, Quaternion::FromEuler(Vector3(0.f, 0.f, Calc::PiOver2))));
    EXPECT_TRUE(Calc::Equals(RotationHalfCircleZ, Quaternion::FromRotationMatrix(Matrix::RotationZ(Calc::PiOver2))));
}

TEST(Quaternion, Inversion)
{
    EXPECT_TRUE(Calc::Equals(Quaternion::Rotate(RotatedUnitX, RotationHalfCircleZ.Inverted()), Vector3::UnitX()));
}

TEST(Quaternion, Operators)
{
    EXPECT_TRUE(Calc::Equals(UnitX + UnitY, Quaternion(1.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(UnitX - UnitX, Quaternion(0.f)));

    EXPECT_TRUE(Calc::Equals(UnitX * 2.f, Quaternion(2.f, 0.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(Quaternion(2.f, 3.f, 4.f, 1.f) * Quaternion(6.f, 7.f, 8.f, 5.f), Quaternion(12.f, 30.f, 24.f, -60.f)));
    EXPECT_TRUE(Calc::Equals(Quaternion(6.f, 7.f, 8.f, 5.f) * Quaternion(2.f, 3.f, 4.f, 1.f), Quaternion(20.f, 14.f, 32.f, -60.f)));

    EXPECT_TRUE(Calc::Equals(UnitX / 2.f, Quaternion(0.5f, 0.f, 0.f, 0.f)));

    Quaternion temp = UnitX;
    EXPECT_TRUE(Calc::Equals(temp += UnitY, Quaternion(1.f, 1.f, 0.f, 0.f)));
    EXPECT_TRUE(Calc::Equals(temp -= UnitX, UnitY));

    temp = Quaternion(1.f);
    EXPECT_TRUE(Calc::Equals(temp *= 2.f, Quaternion(2.f)));
    temp = Quaternion(2.f, 3.f, 4.f, 1.f);
    EXPECT_TRUE(Calc::Equals(temp *= Quaternion(6.f, 7.f, 8.f, 5.f), Quaternion(12.f, 30.f, 24.f, -60.f)));
    temp = Quaternion(6.f, 7.f, 8.f, 5.f);
    EXPECT_TRUE(Calc::Equals(temp *= Quaternion(2.f, 3.f, 4.f, 1.f), Quaternion(20.f, 14.f, 32.f, -60.f)));

    temp = Quaternion(1.f);
    EXPECT_TRUE(Calc::Equals(temp /= 2.f, Quaternion(0.5f)));
}

TEST(Quaternion, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", UnitX), "01.000 ; 00.000 ; 00.000 ; 00.000");
}
