//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_GRAPHICS_H
#define SCRATCH3D_GRAPHICS_H


#include <raylib.h>
#include "Vec3d.h"
#include "MeshObject.h"

class Graphics {
public:
    static void TintColor(Color &c, float dp);
    static void DrawLine(Vec3d p1, Vec3d p2, Color& color);
    static void drawFaceLines(TransformedFace face, Color color);
    static void drawFaceFilled(TransformedFace face, Color color);

};


#endif //SCRATCH3D_GRAPHICS_H
