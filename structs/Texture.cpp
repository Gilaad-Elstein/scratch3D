//
// Created by gilaad on 2/1/20.
//

#include "Texture.h"


namespace Scratch3d{
    Texture::Texture(const char *fName, bool flipVertically, bool flipHorizontally) {

        Image img = LoadImage(fName);
        Image* pImg = &img;
        if (flipVertically) ImageFlipVertical(pImg);
        if (flipHorizontally) ImageFlipHorizontal(pImg);
        Color* rawPixels = GetImageData(*pImg);

        for (int i = 0; i < pImg->height; ++i) {
            std::vector<Color> currLine;
            for (int j = 0; j < pImg->width; ++j) {
                currLine.emplace_back(rawPixels[j + i * pImg->width]);
            }
            data.emplace_back(currLine);
        }
        delete rawPixels;
        UnloadImage(img);
    }

    Color Texture::Sample(float u, float v){
        //data is sorted by lines
        float width = data[0].size();
        float height = data.size();
        return data[v*(height - 1)][u * (width - 1)];
    }

    Texture::Texture() {

    }
}


