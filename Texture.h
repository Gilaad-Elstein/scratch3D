//
// Created by gilaad on 2/1/20.
//

#ifndef SCRATCH3D_TEXTURE_H
#define SCRATCH3D_TEXTURE_H

#include <string>
#include <vector>
#define Font x11FONT
#include "CImg.h"
#undef Font

namespace Scratch3d{
    struct Texture {
        cimg_library::CImg<unsigned char> pixels;
        unsigned width;
        unsigned height;
        explicit Texture(const char* fName);
    };
}





#endif //SCRATCH3D_TEXTURE_H
