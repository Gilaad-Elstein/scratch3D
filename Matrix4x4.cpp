//
// Created by gilaad on 1/22/20.
//

#include <cmath>
#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::MakeIdentityMatrix() {
    Matrix4x4 matrix;
    matrix.m[0][0] = 1.0;
    matrix.m[1][1] = 1.0;
    matrix.m[2][2] = 1.0;
    matrix.m[3][3] = 1.0;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeXRotationMatrix(float angle)
{
    Matrix4x4 matrix;
    matrix.m[0][0] = 1.0;
    matrix.m[1][1] = cos(angle);
    matrix.m[1][2] = sin(angle);
    matrix.m[2][1] = -sin(angle);
    matrix.m[2][2] = cos(angle);
    matrix.m[3][3] = 1.0;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeYRotationMatrix(float angle)
{
    Matrix4x4 matrix;
    matrix.m[0][0] = cos(angle);
    matrix.m[0][2] = sin(angle);
    matrix.m[2][0] = -sin(angle);
    matrix.m[1][1] = 1.0;
    matrix.m[2][2] = cos(angle);
    matrix.m[3][3] = 1.0;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeZRotationMatrix(float angle)
{
    Matrix4x4 matrix;
    matrix.m[0][0] = cos(angle);
    matrix.m[0][1] = sin(angle);
    matrix.m[1][0] = -sin(angle);
    matrix.m[1][1] = cos(angle);
    matrix.m[2][2] = 1.0;
    matrix.m[3][3] = 1.0;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeTranslationMatrix(Vec3d vTranslation)
{
    Matrix4x4 matrix;
    matrix.m[0][0] = 1.0;
    matrix.m[1][1] = 1.0;
    matrix.m[2][2] = 1.0;
    matrix.m[3][3] = 1.0;
    matrix.m[3][0] = -vTranslation.x;
    matrix.m[3][1] = -vTranslation.y;
    matrix.m[3][2] = -vTranslation.z;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeProjectionMatrix(float focalLength,
                                          float xResolution,
                                          float yResolution,
                                          int width,
                                          int height)
{
    Matrix4x4 matrix;
    matrix.m[0][0] = focalLength * width / (2 * xResolution);
    matrix.m[1][1] = focalLength * height / (2 * yResolution);
    matrix.m[0][1] = 0; //Skew
    matrix.m[0][2] = 0; //Principle point X offset
    matrix.m[1][2] = 0; //Principle point Y offset
    matrix.m[2][1] = -1;
    matrix.m[2][2] = 1;
    matrix.m[3][3] = 1;
    return matrix;
}

void Matrix4x4::operator*=(Matrix4x4 other) {
    Matrix4x4 orig = this->Clone();
    for (int c = 0; c < 4; c++)
        for (int r = 0; r < 4; r++)
            m[r][c] = orig.m[r][0] * other.m[0][c] + orig.m[r][1] * other.m[1][c] + orig.m[r][2] * other.m[2][c] + orig.m[r][3] * other.m[3][c];
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 other)  {
    Matrix4x4 matrix = this->Clone();
    matrix *= other;
    return matrix;
}

Matrix4x4 Matrix4x4::Clone() const {
    Matrix4x4 clone;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            clone.m[i][j] = m[i][j];
        }
    }
    return clone;
}

Matrix4x4 Matrix4x4::MakePointAtMatrix(Vec3d &pos, Vec3d &target, Vec3d &up) {
    Vec3d newForward = target - pos;
    newForward.Normalise();

    Vec3d a = newForward * up.DotProduct(newForward);
    up -= a;
    Vec3d newUp = up;
    newUp.Normalise();

    Vec3d newRight = newUp.CrossProduct(newForward);

    // Dimensioning and translation matrix
    Matrix4x4 matrix;
    matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
    matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
    matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
    matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
    return matrix;
}

Matrix4x4 Matrix4x4::MakeInverseMatrix(const Matrix4x4 &matrix) {
    Matrix4x4 inverseMatrix;
    inverseMatrix.m[0][0] = matrix.m[0][0]; inverseMatrix.m[0][1] = matrix.m[1][0]; inverseMatrix.m[0][2] = matrix.m[2][0]; inverseMatrix.m[0][3] = 0.0f;
    inverseMatrix.m[1][0] = matrix.m[0][1]; inverseMatrix.m[1][1] = matrix.m[1][1]; inverseMatrix.m[1][2] = matrix.m[2][1]; inverseMatrix.m[1][3] = 0.0f;
    inverseMatrix.m[2][0] = matrix.m[0][2]; inverseMatrix.m[2][1] = matrix.m[1][2]; inverseMatrix.m[2][2] = matrix.m[2][2]; inverseMatrix.m[2][3] = 0.0f;
    inverseMatrix.m[3][0] = -(matrix.m[3][0] * inverseMatrix.m[0][0] + matrix.m[3][1] * inverseMatrix.m[1][0] + matrix.m[3][2] * inverseMatrix.m[2][0]);
    inverseMatrix.m[3][1] = -(matrix.m[3][0] * inverseMatrix.m[0][1] + matrix.m[3][1] * inverseMatrix.m[1][1] + matrix.m[3][2] * inverseMatrix.m[2][1]);
    inverseMatrix.m[3][2] = -(matrix.m[3][0] * inverseMatrix.m[0][2] + matrix.m[3][1] * inverseMatrix.m[1][2] + matrix.m[3][2] * inverseMatrix.m[2][2]);
    inverseMatrix.m[3][3] = 1.0f;
    return inverseMatrix;
}