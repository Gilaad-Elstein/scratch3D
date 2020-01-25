//
// Created by gilaad on 1/24/20.
//

#include <cmath>
#include "Vec3d.h"

void Vec3d::Normalise() {
    double l = GetLength();
    x /= l;
    y /= l;
    z /= l;
}

double Vec3d::GetLength() const {
    return sqrt(this->DotProduct(*this));
}

double Vec3d::DotProduct(const Vec3d &other) const {
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

Vec3d Vec3d::operator+(double val) const {
    return Vec3d{x + val, y + val, z + val};
}

void Vec3d::operator+=(double val) {
    x += val;
    y += val;
    z += val;
}

Vec3d Vec3d::operator-(double val) const {
    return Vec3d{x - val, y - val, z - val};
}

void Vec3d::operator-=(double val) {
    x -= val;
    y -= val;
    z -= val;
}

Vec3d Vec3d::operator/(double val) const {
    Vec3d v{x, y, z};
    if (val != 0){
        v.x /= val;
        v.y /= val;
        v.z /= val;
    }
    return v;
}

void Vec3d::operator/=(double val) {
    if (val != 0){
        x /= val;
        y /= val;
        z /= val;
    }
}

void Vec3d::operator*=(double val) {
    x *= val;
    y *= val;
    z *= val;
}

Vec3d Vec3d::operator*(double val) const{
    return {x * val, y * val, z * val};
}

Vec3d Vec3d::GetNormal() {
    Vec3d normal{x, y, z};
    normal.Normalise();
    return normal;
}
