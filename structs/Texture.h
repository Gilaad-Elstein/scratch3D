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
    private:
        std::vector<std::vector<Color>> data;

    public:
        Texture(const char *fName, bool flipVertically, bool flipHorizontally);
        Texture();
        Color Sample(float u, float v);
    };
}





#endif //SCRATCH3D_TEXTURE_H
