//
// Created by gilaad on 1/22/20.
//

#ifndef SCRATCH3D__MATRIX4X4_H
#define SCRATCH3D__MATRIX4X4_H


#include "Vec3.h"

struct Vec3;

struct Matrix4x4
{
    float m[4][4] = { 0 };

    Matrix4x4 Clone() const;

    void operator *=(Matrix4x4 other);
    Matrix4x4 operator *(Matrix4x4 other);

    static Matrix4x4 MakeIdentityMatrix();
    static Matrix4x4 MakeXRotationMatrix(float angle);
    static Matrix4x4 MakeYRotationMatrix(float angle);
    static Matrix4x4 MakeZRotationMatrix(float angle);
    static Matrix4x4 MakeTranslationMatrix(Vec3 vTranslation);
    static Matrix4x4 MakePointAtMatrix(Vec3 &pos, Vec3 &target, Vec3 &up);
    static Matrix4x4 MakeInverseMatrix(const Matrix4x4 &matrix);
    static Matrix4x4 MakeProjectionMatrix(float focalLength,
                                          float xResolution,
                                          float yResolution,
                                          int width,
                                          int height);

};

#endif //INC_SCRATCH3D_MATRIX4X4_H