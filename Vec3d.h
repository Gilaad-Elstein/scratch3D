//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_VEC3D_H
#define SCRATCH3D_VEC3D_H


struct Vec3d {
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 1;

    Vec3d()= default;
    Vec3d(double x_, double y_){ x = x_; y = y_;}
    Vec3d(double x_, double y_, double z_){ x = x_; y = y_; z = z_;}

    void Normalise();
    double GetLength() const;
    double DotProduct(const Vec3d &other) const;
    Vec3d CrossProduct(const Vec3d &other) const;


    Vec3d operator *(double val) const;
    void operator *=(double val);

    Vec3d operator /(double val) const;
    void operator /=(double val);

    Vec3d operator+(const Vec3d &other) const;
    void operator+=(const Vec3d &other);

    Vec3d operator-(const Vec3d &other) const;
    void operator-=(const Vec3d &other);

    Vec3d operator+(double val) const;
    void operator+=(double val);

    Vec3d operator-(double val) const;
    void operator-=(double val);

    Vec3d GetNormal();
};


#endif //SCRATCH3D_VEC3D_H
