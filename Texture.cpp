//
// Created by gilaad on 2/1/20.
//

#include <raylib.h>
#include "Texture.h"

namespace Scratch3d{
    Texture::Texture(const char* fName) {
        Image iTexture = LoadImage(fName);
        Texture2D texture = LoadTextureFromImage(iTexture);
        width = iTexture.width;
        height = iTexture.height;
        Color* rawColor = GetImageData(iTexture);
        for (int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x){
                pixelData.emplace_back(rawColor[x + y * width]);
            }
        }
        UnloadImage(iTexture);
        delete rawColor;
    }
}


