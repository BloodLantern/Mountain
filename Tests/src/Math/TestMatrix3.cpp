#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Matrix3 Zero = Matrix3();
constexpr Matrix3 IdentityMatrix = Matrix3::Identity();

constexpr Vector3 One(1.f);
const Matrix3 RotationHalfCircleZ = Matrix3::RotationZ(Calc::PiOver2);

constexpr Matrix3 Symmetric(
    1.f, 2.f, 3.f,
    2.f, 4.f, 5.f,
    3.f, 5.f, 6.f
);
constexpr Matrix3 Antisymmetric(
    1.f, 2.f, 3.f,
    -2.f, 4.f, 5.f,
    -3.f, -5.f, 6.f
);

constexpr Vector3 OneTwoThree(1.f, 2.f, 3.f);

TEST(Matrix3, Constants)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix, Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f)));
}

TEST(Matrix3, CheckFunctions)
{
    EXPECT_TRUE(IdentityMatrix.IsDiagonal());
    EXPECT_FALSE(RotationHalfCircleZ.IsDiagonal());

    EXPECT_TRUE(IdentityMatrix.IsIdentity());
    EXPECT_FALSE(Zero.IsIdentity());
    EXPECT_FALSE(RotationHalfCircleZ.IsIdentity());

    EXPECT_TRUE(Zero.IsNull());
    EXPECT_FALSE(RotationHalfCircleZ.IsNull());

    EXPECT_TRUE(IdentityMatrix.IsSymmetric());
    EXPECT_TRUE(Symmetric.IsSymmetric());
    EXPECT_FALSE(Antisymmetric.IsSymmetric());

    EXPECT_TRUE(IdentityMatrix.IsAntisymmetric());
    EXPECT_TRUE(Antisymmetric.IsAntisymmetric());
    EXPECT_FALSE(Symmetric.IsAntisymmetric());
}

TEST(Matrix3, SmallFunctions)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix.Diagonal(), Vector3(1.f)));

    EXPECT_EQ(IdentityMatrix.Determinant(), 1.f);
    EXPECT_EQ(RotationHalfCircleZ.Determinant(), 1.f);
    EXPECT_EQ(Zero.Determinant(), 0.f);

    EXPECT_TRUE(Calc::Equals(IdentityMatrix, IdentityMatrix.Transposed()));
}

TEST(Matrix3, Multiplication)
{
    constexpr Matrix3 a = Matrix3::Scaling(Vector3(2.f));

    EXPECT_TRUE(Calc::Equals(a * a, Matrix3::Scaling(Vector3(4.f))));

    constexpr Matrix3 b = Matrix3::Scaling(Vector3(-5.f));

    constexpr Matrix3 ab = a * b;

    EXPECT_TRUE(Calc::Equals(ab * One, Vector3(-10.f)));
}

TEST(Matrix3, Inversion)
{
    EXPECT_TRUE(Calc::Equals(RotationHalfCircleZ * RotationHalfCircleZ.Inverted(), IdentityMatrix));

    constexpr Matrix3 temp(
        1.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        1.f, 1.f, 1.f
    );

    EXPECT_THROW((void) temp.Inverted(), std::invalid_argument);
}

TEST(Matrix3, Rotation)
{
    EXPECT_TRUE(Calc::Equals(Matrix3::RotationX(Calc::PiOver2) * Vector3::UnitY(), Vector3::UnitZ()));
    EXPECT_TRUE(Calc::Equals(Matrix3::RotationY(Calc::PiOver2) * Vector3::UnitZ(), Vector3::UnitX()));
    EXPECT_TRUE(Calc::Equals(Matrix3::RotationZ(Calc::PiOver2) * Vector3::UnitX(), Vector3::UnitY()));
}

TEST(Matrix3, Scaling)
{
    EXPECT_TRUE(Calc::Equals(Matrix3::Scaling(OneTwoThree) * One, OneTwoThree));
}

TEST(Matrix3, Subscript)
{
    EXPECT_THROW((void) Zero.At(3, 0), std::out_of_range);
    EXPECT_THROW((void) Zero.At(0, 3), std::out_of_range);
    EXPECT_THROW((void) Zero.At(3, 3), std::out_of_range);
    EXPECT_NO_THROW((void) Zero.At(0, 1));
}

TEST(Matrix3, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ; 00.000 ] [ 00.000 ; 01.000 ; 00.000 ] [ 00.000 ; 00.000 ; 01.000 ]");
    EXPECT_EQ(std::format("{0:m06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ; 00.000 ]\n[ 00.000 ; 01.000 ; 00.000 ]\n[ 00.000 ; 00.000 ; 01.000 ]");
}
