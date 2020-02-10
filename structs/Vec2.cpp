//
// Created by gilaad on 2/1/20.
//

#include "Vec2.h"

Vec2 Vec2::operator-(const Vec2 &other) const {
    return Vec2{u - other.u, v - other.v};
}

Vec2 Vec2::operator/(const float val) const {
    return Vec2{u / val, v / val};
}

Vec2 Vec2::operator*(const float val) const {
    return Vec2{u * val, v * val};
}

Vec2 Vec2::operator+=(const Vec2 &other) {
    u += other.u;
    v += other.v;
}

Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2{u + other.u, v + other.v};
}

Vec2::Vec2(float _u, float _v) {
    u = _u;
    v = _v;
}
