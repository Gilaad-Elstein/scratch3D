//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_VEC3D_H
#define SCRATCH3D_VEC3D_H


#include "Matrix4x4.h"

struct Matrix4x4;

struct Vec3d {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;

    Vec3d()= default;
    Vec3d(float x_, float y_){ x = x_; y = y_;}
    Vec3d(float x_, float y_, float z_){ x = x_; y = y_; z = z_;}

    void Normalise();
    float GetLength() const;
    float DotProduct(const Vec3d &other) const;
    Vec3d CrossProduct(const Vec3d &other) const;
    Vec3d GetNormal();

    void rotate(const Matrix4x4& mRotation);

    Vec3d operator *(float val) const;
    void operator *=(float val);

    Vec3d operator /(float val) const;
    void operator /=(float val);

    Vec3d operator+(const Vec3d &other) const;
    void operator+=(const Vec3d &other);

    Vec3d operator-(const Vec3d &other) const;
    void operator-=(const Vec3d &other);

    Vec3d operator+(float val) const;
    void operator+=(float val);

    Vec3d operator-(float val) const;
    void operator-=(float val);

    Vec3d operator*(const Matrix4x4 &matrix) const;
    void operator*=(const Matrix4x4 &matrix);
};


#endif //SCRATCH3D_VEC3D_H
