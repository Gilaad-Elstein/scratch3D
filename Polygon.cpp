//
// Created by gilaad on 1/24/20.
//

#include <tuple>
#include <algorithm>
#include "Polygon.h"

void Polygon::InvertXY() {
    for(auto& point : points){
        point.x *= -1;
        point.y *= -1;
    }
}

Polygon Polygon::Clone() {
    Polygon p{};
    for(auto& point : points){
        p.points.emplace_back(point);
    }
    return p;
}

std::tuple<int, int> Polygon::GetMinMaxYVals() const{
    double min = points[0].y, max = points[0].y;
    for(auto& point : points){
        if (point.y < min){ min = point.y;}
        if (point.y > max){ max = point.y;}
    }
    std::tuple<int, int> vals = std::make_tuple(static_cast<int>(min), static_cast<int>(max));
    return vals;
}

std::vector<double> Polygon::GetYLineNodes(int y) const{
    std::vector<double> nodes;
    for (int i = 0; i < points.size(); ++i) {
        int nextI = (i != points.size() - 1) ? i+1 : 0;
        auto yD = static_cast<double>(y);
        if((points[i].y >= yD && points[nextI].y < yD) ||
           (points[i].y <= yD && points[nextI].y > yD)){
            double val = points[i].x + (yD - points[i].y) / ((points[nextI].y - points[i].y) / (points[nextI].x - points[i].x));
            nodes.emplace_back(val);
        }
    }
    std::sort(nodes.begin(), nodes.end());
    return nodes;
}

Vec3d Polygon::GetNormalizedNormal() const{
    Vec3d normal, line1, line2;
    line1 = points[1] - points[0];
    line2 = points[2] - points[0];
    normal = line1.CrossProduct(line2);
    normal.Normalise();
    return normal;
}

std::tuple<double, double> Polygon::GetZValues(int y){
    double zLeft = -std::numeric_limits<double>::infinity();
    double zRight = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < points.size(); ++i) {
        int nextI = (i != points.size() - 1) ? i+1 : 0;
        auto yD = static_cast<double>(y);
        if((points[i].y >= yD && points[nextI].y < yD) ||
           (points[i].y <= yD && points[nextI].y > yD)){
            if (zLeft == -std::numeric_limits<double>::infinity()){
                zLeft = points[i].z + (yD - points[i].y) / ((points[nextI].y - points[i].y) / (points[nextI].z - points[i].z));
                continue;
            }
            if (zRight == -std::numeric_limits<double>::infinity()){
                zRight = points[i].z + (yD - points[i].y) / ((points[nextI].y - points[i].y) / (points[nextI].z - points[i].z));
            }
        }
    }
    return std::make_tuple(zLeft, zRight);
}

Polygon Polygon::GetTexturePolygon(){
    Polygon p;
    for(auto& point : textureCoords){
        p.points.emplace_back(point);
    }
    return p;
}

void Polygon::ScaleToScreenSpace(double w, double h) {
    for(auto& point : points){
        point.x = (point.x*h/w + 1) * w / 2;
        point.y = (point.y + 1) * h / 2;
    }
}

void Polygon::Translate2D(double x, double y) {
    for(auto& point : points){
        point.x += x;
        point.y += y;
    }
}

void Polygon::Scale2D(double x, double y) {
    for(auto& point : points){
        point.x *= x;
        point.y *= y;
    }
}

void Polygon::FlipNormalizedPolyVertically() {
    for(auto& point : points){
        point.y = 1 - point.y;
    }
}
