//
// Created by gilaad on 1/24/20.
//

#include <cmath>
#include "Vec3d.h"
#include "Matrix4x4.h"

void Vec3d::Normalise() {
    float l = GetLength();
    x /= l;
    y /= l;
    z /= l;
}

float Vec3d::GetLength() const {
    return sqrt(this->DotProduct(*this));
}

float Vec3d::DotProduct(const Vec3d &other) const {
    return x*other.x + y*other.y + z * other.z;
}

Vec3d Vec3d::CrossProduct(const Vec3d &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}


Vec3d Vec3d::operator+(const Vec3d &other) const{
    return Vec3d {x + other.x,
                  y + other.y,
                  z + other.z};
}

void Vec3d::operator+=(const Vec3d &other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

Vec3d Vec3d::operator-(const Vec3d &other) const{
    return Vec3d {x - other.x,
                  y - other.y,
                  z - other.z};
}

void Vec3d::operator-=(const Vec3d &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

Vec3d Vec3d::operator+(float val) const {
    return Vec3d{x + val, y + val, z + val};
}

void Vec3d::operator+=(float val) {
    x += val;
    y += val;
    z += val;
}

Vec3d Vec3d::operator-(float val) const {
    return Vec3d{x - val, y - val, z - val};
}

void Vec3d::operator-=(float val) {
    x -= val;
    y -= val;
    z -= val;
}

Vec3d Vec3d::operator/(float val) const {
    Vec3d v{x, y, z};
    if (val != 0){
        v.x /= val;
        v.y /= val;
        v.z /= val;
    }
    return v;
}

void Vec3d::operator/=(float val) {
    if (val != 0){
        x /= val;
        y /= val;
        z /= val;
    }
}

void Vec3d::operator*=(float val) {
    x *= val;
    y *= val;
    z *= val;
}

Vec3d Vec3d::operator*(float val) const{
    return {x * val, y * val, z * val};
}

Vec3d Vec3d::GetNormal() {
    Vec3d normal{x, y, z};
    normal.Normalise();
    return normal;
}

void Vec3d::rotate(const Matrix4x4& mRotation) {
    *this *= mRotation;
}

Vec3d Vec3d::operator*(const Matrix4x4 &matrix) const{
    Vec3d v{x, y, z};
    v *= matrix;
    return v;
}

void Vec3d::operator*=(const Matrix4x4 &matrix) {
    float origX = x, origY = y, origZ = z, origW = w;
    x = origX * matrix.m[0][0] + origY * matrix.m[1][0] + origZ * matrix.m[2][0] + origW * matrix.m[3][0];
    y = origX * matrix.m[0][1] + origY * matrix.m[1][1] + origZ * matrix.m[2][1] + origW * matrix.m[3][1];
    z = origX * matrix.m[0][2] + origY * matrix.m[1][2] + origZ * matrix.m[2][2] + origW * matrix.m[3][2];
    w = origX * matrix.m[0][3] + origY * matrix.m[1][3] + origZ * matrix.m[2][3] + origW * matrix.m[3][3];
}
