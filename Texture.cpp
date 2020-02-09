//
// Created by gilaad on 2/1/20.
//

#include "Texture.h"


namespace Scratch3d{
    Texture::Texture(const char* fName) {
        pixels.assign(fName);
        pixels.rotate(180);
        width = pixels.width();
        height = pixels.height();
    }
}


