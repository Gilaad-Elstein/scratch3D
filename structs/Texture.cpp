//
// Created by gilaad on 2/1/20.
//

#include "Texture.h"


namespace Scratch3d{
    Texture::Texture(const char *fName, int numRotateCCW = 0, bool flipVertically = false, bool flipHorizontally = false) {

        Image img = LoadImage(fName);
        Image* pImg = &img;
        for (int k = 0; k < numRotateCCW; ++k) {
            ImageRotateCCW(pImg);
        }
        if (flipVertically) ImageFlipVertical(pImg);
        if (flipHorizontally) ImageFlipHorizontal(pImg);
        Color* rawPixels = GetImageData(*pImg);
        width = pImg->width;
        height = pImg->height;

        for (int i = 0; i < height; ++i) {
            std::vector<Color> currLine;
            for (int j = 0; j < width; ++j) {
                currLine.emplace_back(rawPixels[j + i * width]);
            }
            data.emplace_back(currLine);
        }
        delete rawPixels;
    }

    Color Texture::Sample(float u, float v){
        return data[v*(height - 1)][u*(width - 1)]; //data is sorted by lines
    }

    Texture::Texture() {

    }
}


