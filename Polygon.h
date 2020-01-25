//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_POLYGON_H
#define SCRATCH3D_POLYGON_H


#include <vector>
#include "Vec3d.h"

struct Polygon {
    std::vector<Vec3d> points;
    std::vector<Vec3d> textureCoords;

    void InvertXY();

    Polygon Clone();

    std::tuple<int, int> GetMinMaxYVals() const;

    std::vector<double> GetYLineNodes(int y) const;

    Vec3d GetNormalizedNormal() const;

    std::tuple<double, double> GetZValues(int y);

    Polygon GetTexturePolygon();

    void ScaleToScreenSpace(double w, double h);

    void Translate2D(double x, double y);

    void Scale2D(double x, double y);

    void FlipNormalizedPolyVertically();
};


#endif //SCRATCH3D_POLYGON_H
