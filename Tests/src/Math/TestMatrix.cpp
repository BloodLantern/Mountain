#include "gtest/gtest.h"

#include <Mountain/Math/Math.hpp>

constexpr Matrix Zero = Matrix();
constexpr Matrix IdentityMatrix = Matrix::Identity();

constexpr Vector3 One(1.f);
const Matrix RotationHalfCircleZ = Matrix::RotationZ(Calc::PiOver2);
const Matrix Trs = Matrix::Trs(One, RotationHalfCircleZ, Vector3(2.f));

constexpr Matrix Symmetric(
    1.f, 2.f, 3.f, 4.f,
    2.f, 5.f, 6.f, 7.f,
    3.f, 6.f, 8.f, 9.f,
    4.f, 7.f, 9.f, 10.f
);
constexpr Matrix Antisymmetric(
    1.f, 2.f, 3.f, 4.f,
   -2.f, 5.f, 6.f, 7.f,
   -3.f,-6.f, 8.f, 9.f,
   -4.f,-7.f,-9.f, 10.f
);

constexpr Vector3 OneTwoThree(1.f, 2.f, 3.f);

TEST(Matrix, Constants)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix, Matrix(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f)));
}

TEST(Matrix, CheckFunctions)
{
    EXPECT_TRUE(IdentityMatrix.IsDiagonal());
    EXPECT_FALSE(Trs.IsDiagonal());

    EXPECT_TRUE(IdentityMatrix.IsIdentity());
    EXPECT_FALSE(Zero.IsIdentity());
    EXPECT_FALSE(Trs.IsIdentity());

    EXPECT_TRUE(Zero.IsNull());
    EXPECT_FALSE(Trs.IsNull());

    EXPECT_TRUE(IdentityMatrix.IsSymmetric());
    EXPECT_TRUE(Symmetric.IsSymmetric());
    EXPECT_FALSE(Antisymmetric.IsSymmetric());
    EXPECT_FALSE(Trs.IsSymmetric());

    EXPECT_TRUE(IdentityMatrix.IsAntisymmetric());
    EXPECT_TRUE(Antisymmetric.IsAntisymmetric());
    EXPECT_FALSE(Symmetric.IsAntisymmetric());
    EXPECT_FALSE(Trs.IsAntisymmetric());
}

TEST(Matrix, SmallFunctions)
{
    EXPECT_TRUE(Calc::Equals(IdentityMatrix.Diagonal(), Vector4(1.f)));

    EXPECT_EQ(IdentityMatrix.Determinant(), 1.f);
    EXPECT_EQ(Trs.Determinant(), 8.f);
    EXPECT_EQ(Zero.Determinant(), 0.f);

    EXPECT_TRUE(Calc::Equals(IdentityMatrix, IdentityMatrix.Transposed()));
}

TEST(Matrix, Multiplication)
{
    constexpr Matrix t = Matrix::Translation(One);

    EXPECT_TRUE(Calc::Equals(t * t, Matrix::Translation(Vector3(2.f))));

    constexpr Matrix s = Matrix::Scaling(Vector3(-5.f));

    constexpr Matrix ts = t * s;

    EXPECT_TRUE(Calc::Equals(ts * One, Vector3(-4.f)));
}

TEST(Matrix, Inversion)
{
    EXPECT_TRUE(Calc::Equals(Trs * Trs.Inverted(), IdentityMatrix));

    constexpr Matrix temp(
        1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f
    );

    EXPECT_THROW((void) temp.Inverted(), std::invalid_argument);
}

TEST(Matrix, Translation)
{
    EXPECT_TRUE(Calc::Equals(Matrix::Translation(OneTwoThree) * One, Vector3(2.f, 3.f, 4.f)));
}

TEST(Matrix, Rotation)
{
    EXPECT_TRUE(Calc::Equals(Matrix::RotationZ(Calc::PiOver2) * Vector3::UnitX(), Vector3::UnitY()));
}

TEST(Matrix, Scaling)
{
    EXPECT_TRUE(Calc::Equals(Matrix::Scaling(OneTwoThree) * One, OneTwoThree));
}

TEST(Matrix, TRS)
{
    EXPECT_TRUE(Calc::Equals(Matrix::Trs(One, Vector3(0.f, 0.f, Calc::PiOver2), Vector3(2.f)) * One, Vector3(-1.f, 3.f, 3.f)));
}

TEST(Matrix, Subscript)
{
    EXPECT_THROW((void) Zero.At(4, 0), std::out_of_range);
    EXPECT_THROW((void) Zero.At(0, 4), std::out_of_range);
    EXPECT_THROW((void) Zero.At(4, 4), std::out_of_range);
    EXPECT_NO_THROW((void) Zero.At(1, 2));
}

TEST(Matrix, Formatting)
{
    EXPECT_EQ(std::format("{0:06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ; 00.000 ; 00.000 ] [ 00.000 ; 01.000 ; 00.000 ; 00.000 ] [ 00.000 ; 00.000 ; 01.000 ; 00.000 ] [ 00.000 ; 00.000 ; 00.000 ; 01.000 ]");
    EXPECT_EQ(std::format("{0:m06.3f}", IdentityMatrix), "[ 01.000 ; 00.000 ; 00.000 ; 00.000 ]\n[ 00.000 ; 01.000 ; 00.000 ; 00.000 ]\n[ 00.000 ; 00.000 ; 01.000 ; 00.000 ]\n[ 00.000 ; 00.000 ; 00.000 ; 01.000 ]");
}
