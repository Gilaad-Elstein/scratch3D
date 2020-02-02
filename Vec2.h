//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_VEC2_H
#define SCRATCH3D_VEC2_H


struct Vec2 {
    float u;
    float v;

    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator+=(const Vec2 &other);
    Vec2 operator/(float val) const;
    Vec2 operator*(float val) const;

};


#endif //SCRATCH3D_VEC2_H
