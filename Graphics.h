//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_GRAPHICS_H
#define SCRATCH3D_GRAPHICS_H


#include <raylib.h>
#include "Vec3.h"
#include "Mesh.h"
#include "Texture.h"

using Scratch3d::TransformedFace;

class Graphics {
public:
    static void TintColor(Color &c, float dp);
    static void DrawLine(Vec3 p1, Vec3 p2, Color& color);
    static void drawFaceLines(TransformedFace face, Color color);
    static void drawFaceFilled(TransformedFace& face, Color color);
    static void drawFaceTextured(TransformedFace &face, Scratch3d::Texture &texture);
};


#endif //SCRATCH3D_GRAPHICS_H
