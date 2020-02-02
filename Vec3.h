//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_VEC3_H
#define SCRATCH3D_VEC3_H


#include "Matrix4x4.h"

struct Matrix4x4;

struct Vec3 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;

    Vec3()= default;
    Vec3(float x_, float y_){ x = x_; y = y_;}
    Vec3(float x_, float y_, float z_){ x = x_; y = y_; z = z_;}

    void Normalise();
    float GetLength() const;
    float DotProduct(const Vec3 &other) const;
    Vec3 CrossProduct(const Vec3 &other) const;

    void rotate(const Matrix4x4& mRotation);

    Vec3 operator *(float val) const;
    void operator *=(float val);

    Vec3 operator /(float val) const;
    void operator /=(float val);

    Vec3 operator+(const Vec3 &other) const;
    void operator+=(const Vec3 &other);

    Vec3 operator-(const Vec3 &other) const;
    void operator-=(const Vec3 &other);

    Vec3 operator+(float val) const;
    void operator+=(float val);

    Vec3 operator-(float val) const;
    void operator-=(float val);

    Vec3 operator*(const Matrix4x4 &matrix) const;
    void operator*=(const Matrix4x4 &matrix);
};


#endif //SCRATCH3D_VEC3_H
