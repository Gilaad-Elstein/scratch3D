//
// Created by gilaad on 2/1/20.
//

#include "Texture.h"


namespace Scratch3d{
    Texture::Texture(const char* fName) {
        pixels.assign(fName);;
        width = pixels.width();
        height = pixels.height();
    }

    Texture::Texture() {

    }
}


