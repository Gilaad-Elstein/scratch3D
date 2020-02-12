//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_TEXTURE_H
#define SCRATCH3D_TEXTURE_H

#include <string>
#include <vector>
#include "raylib.h"

namespace Scratch3d{
    struct Texture {
        Texture();

        std::vector<std::vector<Color>> data;
        unsigned width;
        unsigned height;
        explicit Texture(const char *fName, int numRotateCCW, bool flipVertically, bool flipHorizontally);

        Color Sample(float u, float v);
    };
}





#endif //SCRATCH3D_TEXTURE_H
