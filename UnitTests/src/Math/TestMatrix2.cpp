#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Matrix2 Zero = Matrix2();
constexpr Matrix2 IdentityMatrix = Matrix2::Identity();

constexpr Vector2 One(1.f);
const Matrix2 RotationHalfCircleZ = Matrix2::RotationZ(Calc::PiOver2);

constexpr Matrix2 Symmetric(
    1.f, 2.f,
    2.f, 3.f
);
constexpr Matrix2 Antisymmetric(
    1.f, 2.f,
    -2.f, 3.f
);

constexpr Vector2 OneTwoThree(1.f, 2.f);

TEST(Matrix2, Constants)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix, Matrix2(1.f, 0.f, 0.f, 1.f)));
}

TEST(Matrix2, CheckFunctions)
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

TEST(Matrix2, SmallFunctions)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix.Diagonal(), Vector2(1.f)));

    EXPECT_EQ(IdentityMatrix.Determinant(), 1.f);
    EXPECT_EQ(RotationHalfCircleZ.Determinant(), -1.f);
    EXPECT_EQ(Zero.Determinant(), 0.f);

    EXPECT_TRUE(Calc::Equals(IdentityMatrix, IdentityMatrix.Transposed()));
}

TEST(Matrix2, Multiplication)
{
    constexpr Matrix2 a = Matrix2::Scaling(Vector2(2.f));

    EXPECT_TRUE(Calc::Equals(a * a, Matrix2::Scaling(Vector2(4.f))));

    constexpr Matrix2 b = Matrix2::Scaling(Vector2(-5.f));

    constexpr Matrix2 ab = a * b;

    EXPECT_TRUE(Calc::Equals(ab * One, Vector2(-10.f)));
}

TEST(Matrix2, Inversion)
{
    EXPECT_TRUE(Calc::Equals(RotationHalfCircleZ * RotationHalfCircleZ.Inverted(), IdentityMatrix));

    constexpr Matrix2 temp(
        1.f, 1.f,
        1.f, 1.f
    );

    EXPECT_THROW((void) temp.Inverted(), std::invalid_argument);
}

TEST(Matrix2, Rotation)
{
    EXPECT_TRUE(Calc::Equals(Matrix2::RotationZ(Calc::PiOver2) * Vector2::UnitX(), Vector2::UnitY()));
}

TEST(Matrix2, Scaling)
{
    EXPECT_TRUE(Calc::Equals(Matrix2::Scaling(OneTwoThree) * One, OneTwoThree));
}

TEST(Matrix2, Subscript)
{
    EXPECT_THROW((void) Zero.At(2, 0), std::out_of_range);
    EXPECT_THROW((void) Zero.At(0, 2), std::out_of_range);
    EXPECT_THROW((void) Zero.At(2, 2), std::out_of_range);
    EXPECT_NO_THROW((void) Zero.At(0, 1));
}

TEST(Matrix2, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ] [ 00.000 ; 01.000 ]");
    EXPECT_EQ(std::format("{0:m06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ]\n[ 00.000 ; 01.000 ]");
}
