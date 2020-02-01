//
// Created by gilaad on 1/22/20.
//

#ifndef INC_3DEDU_MATRIX4X4_H
#define INC_3DEDU_MATRIX4X4_H


#include "Vec3d.h"

struct Vec3d;

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
    static Matrix4x4 MakeTranslationMatrix(Vec3d vTranslation);
    static Matrix4x4 MakePointAtMatrix(Vec3d &pos, Vec3d &target, Vec3d &up);
    static Matrix4x4 MakeInverseMatrix(const Matrix4x4 &matrix);
    static Matrix4x4 MakeProjectionMatrix(float focalLength,
                                          float xResolution,
                                          float yResolution,
                                          int width,
                                          int height);

};

#endif //INC_3DEDU_MATRIX4X4_H