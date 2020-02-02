//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_TEXTURE_H
#define SCRATCH3D_TEXTURE_H

#include <string>
#include <vector>

namespace Scratch3d{
    struct Texture {
        std::vector<Color> pixelData;
        int width;
        int height;
        explicit Texture(const char* fName);
    };
}





#endif //SCRATCH3D_TEXTURE_H
