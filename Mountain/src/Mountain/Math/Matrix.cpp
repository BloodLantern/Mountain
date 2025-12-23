
#include "Mountain/Math/Matrix.hpp"

#include <iostream>

Matrix Matrix::Rotation(const f32 angle, const Vector3& axis) noexcept
{
    return Rotation(std::cos(angle), std::sin(angle), axis);
}

void Matrix::Rotation(const f32 angle, const Vector3& axis, Matrix* result) noexcept
{
    Rotation(std::cos(angle), std::sin(angle), axis, result);
}

Matrix Matrix::RotationX(const f32 angle) noexcept
{
    return RotationX(std::cos(angle), std::sin(angle));
}

void Matrix::RotationX(const f32 angle, Matrix* result) noexcept
{
    RotationX(std::cos(angle), std::sin(angle), result);
}

Matrix Matrix::RotationY(const f32 angle) noexcept
{
    return RotationY(std::cos(angle), std::sin(angle));
}

void Matrix::RotationY(const f32 angle, Matrix* result) noexcept
{
    RotationY(std::cos(angle), std::sin(angle), result);
}

Matrix Matrix::RotationZ(const f32 angle) noexcept
{
    return RotationZ(std::cos(angle), std::sin(angle));
}

void Matrix::RotationZ(const f32 angle, Matrix* result) noexcept
{
    RotationZ(std::cos(angle), std::sin(angle), result);
}

Matrix Matrix::Rotation(const Vector3& rotation) noexcept
{
    return RotationZ(rotation.z)
        * RotationY(rotation.y)
        * RotationX(rotation.x);
}

void Matrix::Rotation(const Vector3& rotation, Matrix* result) noexcept
{
    RotationZ(rotation.z, result);
    Matrix temp;
    RotationY(rotation.y, &temp);
    *result *= temp;
    RotationX(rotation.x, &temp);
    *result *= temp;
}

Matrix Matrix::Rotation(const f32 cos, const f32 sin, const Vector3& axis) noexcept
{
    const f32 c2 = 1.f - cos;
    Vector3 v = axis.Normalized();

    return Matrix(
        SQ(v.x) * c2 + cos, v.y * v.x * c2 - v.z * sin, v.z * v.x * c2 + v.y * sin, 0.f,
        v.x * v.y * c2 - v.z * sin, SQ(v.y) * c2 + cos, v.z * v.y * c2 - v.x * sin, 0.f,
        v.x * v.z * c2 - v.y * sin, v.y * v.z * c2 + v.x * sin, SQ(v.z) * c2 + cos, 0.f,
        0.f, 0.f, 0.f,                                                              1.f
    );
}

void Matrix::Rotation(const f32 cos, const f32 sin, const Vector3& axis, Matrix* result) noexcept
{
    const f32 c2 = 1.f - cos;
    Vector3 v = axis.Normalized();

    *result = Matrix(
        SQ(v.x) * c2 + cos, v.y * v.x * c2 - v.z * sin, v.z * v.x * c2 + v.y * sin, 0.f,
        v.x * v.y * c2 - v.z * sin, SQ(v.y) * c2 + cos, v.z * v.y * c2 - v.x * sin, 0.f,
        v.x * v.z * c2 - v.y * sin, v.y * v.z * c2 + v.x * sin, SQ(v.z) * c2 + cos, 0.f,
        0.f, 0.f, 0.f,                                                              1.f
    );
}

Matrix Matrix::Trs(const Vector3& translation, const Vector3& rotation, const Vector3& scale) noexcept
{
    return Trs(translation, Rotation(rotation), scale);
}

void Matrix::Trs(const Vector3& translation, const Vector3& rotation, const Vector3& scale, Matrix* result) noexcept
{
    Trs(translation, Rotation(rotation), scale, result);
}

Matrix Matrix::Trs(const Vector3& translation, const f32 rotationAngle, const Vector3& rotationAxis, const Vector3& scale) noexcept
{
    return Trs(translation, Rotation(rotationAngle, rotationAxis), scale);
}

void Matrix::Trs(const Vector3& translation, const f32 rotationAngle, const Vector3& rotationAxis, const Vector3& scale, Matrix* result) noexcept
{
    Trs(translation, Rotation(rotationAngle, rotationAxis), scale, result);
}

Matrix Matrix::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept
{
    Matrix result;
    LookAt(eye, center, up, &result);
    return result;
}

void Matrix::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix* result) noexcept
{
    const Vector3 f((center - eye).Normalized());
    const Vector3 s(Vector3::Cross(f, up).Normalized());
    const Vector3 u(Vector3::Cross(s, f));

    *result = Matrix(
        s.x, s.y, s.z, -Vector3::Dot(s, eye),
        u.x, u.y, u.z, -Vector3::Dot(u, eye),
        -f.x, -f.y, -f.z, Vector3::Dot(f, eye),
        0.f, 0.f, 0.f, 1.f
    );
}

Matrix Matrix::Perspective(const f32 fov, const f32 aspectRatio, const f32 near, const f32 far)
{
    Matrix result;
    Perspective(fov, aspectRatio, near, far, &result);
    return result;
}

void Matrix::Perspective(const f32 fov, const f32 aspectRatio, const f32 near, const f32 far, Matrix* result)
{
    if (near > far) [[unlikely]]
        throw std::invalid_argument("Near must be smaller than far.");

    const f32 range = far - near;
    const f32 tanHalfFov = std::tan(fov / 2.f);

    *result = Matrix(
        1.f / (tanHalfFov * aspectRatio), 0.f, 0.f, 0.f,
        0.f, 1.f / tanHalfFov, 0.f, 0.f,
        0.f, 0.f, -(far + near) / range, -(2.f * far * near) / range,
        0.f, 0.f, -1.f, 0.f
    );
}

void Matrix::DebugPrint() const noexcept
{
    std::cout << "{ "
        << m00 << ' ' << m10 << ' ' << m20 << ' ' << m30 << " }\n{ "
        << m01 << ' ' << m11 << ' ' << m21 << ' ' << m31 << " }\n{ "
        << m02 << ' ' << m12 << ' ' << m22 << ' ' << m32 << " }\n{ "
        << m03 << ' ' << m13 << ' ' << m23 << ' ' << m33 << " }\n";
}

bool Matrix::Decompose(
    Vector3* const translation,
    Quaternion* const orientation,
    Vector3* const scale,
    Vector3* const skew,
    Vector4* const perspective
) const
{
    // Function from glm

    Matrix localMatrix(*this);

    if (Calc::IsZero(localMatrix.m33))
        return false;

    // Normalize the matrix.
    const f32 invm33 = 1.f / localMatrix.m33;
    f32* const matrix = localMatrix.Data();

    for (u32 i = 0; i < 16; i++)
        matrix[i] *= invm33;

    Matrix perspectiveMatrix(localMatrix);
    perspectiveMatrix.m30 = 0.f;
    perspectiveMatrix.m31 = 0.f;
    perspectiveMatrix.m32 = 0.f;
    perspectiveMatrix.m33 = 1.f;

    if (Calc::IsZero(perspectiveMatrix.Determinant(), 0.f))
        return false;

    // First, isolate perspective. This is the messiest.
    if (Calc::IsZero(localMatrix.m30, 0.f) ||
        Calc::IsZero(localMatrix.m31, 0.f) ||
        Calc::IsZero(localMatrix.m32, 0.f))
    {
        // rightHandSide is the right hand side of the equation.
        Vector4 rightHandSide(localMatrix.m03, localMatrix.m13, localMatrix.m23, localMatrix.m33);

        Matrix inversePerspectiveMatrix = perspectiveMatrix.Inverted();
        Matrix transposedInversePerspectiveMatrix = inversePerspectiveMatrix.Transposed();

        *perspective = transposedInversePerspectiveMatrix * rightHandSide;

        // Clear the perspective partition
        localMatrix.m30 = localMatrix.m13 = localMatrix.m23 = 0.f;
        localMatrix.m33 = 1.f;
    }
    else
    {
        *perspective = Vector4(0.f, 0.f, 0.f, 1.f);
    }

    // Next take care of translation (easy).
    *translation = Vector3(localMatrix[3]);
    Vector4& localMatrixColumn4 = reinterpret_cast<Vector4&>(localMatrix.m03);
    localMatrixColumn4 = Vector4(0.f, 0.f, 0.f, localMatrix.m33);

    // Now get scale and shear.
    Matrix3 row = static_cast<Matrix3>(localMatrix);

    // Compute X scale factor and normalize first row.
    scale->x = row[0].Length();

    row[0] = row[0].Rescaled(1.f);

    // Compute XY shear factor and make 2nd row orthogonal to 1st.
    skew->z = Vector3::Dot(row[0], row[1]);
    row[1] = Vector3::Combine(row[1], row[0], 1.f, -skew->z);

    // Now, compute Y scale and normalize 2nd row.
    scale->y = row[1].Length();
    row[1] = row[1].Rescaled(1.f);
    skew->z /= scale->y;

    // Compute XZ and YZ shears, orthogonalize 3rd row.
    skew->y = Vector3::Dot(row[0], row[2]);
    row[2] = Vector3::Combine(row[2], row[0], 1.f, -skew->y);
    skew->x = Vector3::Dot(row[1], row[2]);
    row[2] = Vector3::Combine(row[2], row[1], 1.f, -skew->x);

    // Next, get Z scale and normalize 3rd row.
    scale->z = row[2].Length();
    row[2] = row[2].Rescaled(1.f);
    skew->y /= scale->z;
    skew->x /= scale->z;

    // At this point, the matrix (in rows[]) is orthonormal.
    // Check for a coordinate system flip.  If the determinant
    // is -1, then negate the matrix and the scaling factors.
    Vector3 pdum3 = Vector3::Cross(row[1], row[2]);
    if (Vector3::Dot(row[0], pdum3) < 0)
    {
        for(u32 i = 0; i < 3; i++)
        {
            scale[i] *= -1.f;
            row[i] *= -1.f;
        }
    }

    s32 i, j, k = 0;
    f32 root = 0.f;
    const f32 trace = row[0].x + row[1].y + row[2].z;

    if (trace > 0.f)
    {
        root = sqrt(trace + 1.0f);
        orientation->W() = 0.5f * root;
        root = 0.5f / root;
        orientation->X() = root * (row[1].z - row[2].y);
        orientation->Y() = root * (row[2].x - row[0].z);
        orientation->Z() = root * (row[0].y - row[1].x);
    }
    else
    {
        static s32 next[3] = {1, 2, 0};
        i = 0;
        if (row[1].y > row[0].x)
            i = 1;
        if (row[2].z > row[i][i])
            i = 2;
        j = next[i];
        k = next[j];

        root = sqrt(row[i][i] - row[j][j] - row[k][k] + 1.0f);

        Quaternion& ref = *orientation;
        ref[i] = 0.5f * root;
        root = 0.5f / root;
        ref[j] = root * (row[i][j] + row[j][i]);
        ref[k] = root * (row[i][k] + row[k][i]);
        ref.W() = root * (row[j][k] - row[k][j]);
    }

    return true;
}

std::ostream& operator<<(std::ostream &out, const Matrix &m)
{
    return out << "{ { " << m.m00 << ' ' << m.m01 << ' ' << m.m02 << ' ' << m.m03 << " } { "
        << m.m10 << ' ' << m.m11 << ' ' << m.m12 << ' ' << m.m13 << " } { "
        << m.m20 << ' ' << m.m21 << ' ' << m.m22 << ' ' << m.m23 << " } { "
        << m.m30 << ' ' << m.m31 << ' ' << m.m32 << ' ' << m.m33 << " } }";
}
