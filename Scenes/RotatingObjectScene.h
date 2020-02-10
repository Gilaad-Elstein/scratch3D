//
// Created by gilaad on 2/10/20.
//

#ifndef SCRATCH3D_ROTATINGOBJECTSCENE_H
#define SCRATCH3D_ROTATINGOBJECTSCENE_H


#include "../Scene.h"

class RotatingObjectScene : public Scene {
    void Update() override;

    float thetaX = 0;
    float thetaY = 0;
    float thetaZ = 0;

};


#endif //SCRATCH3D_ROTATINGOBJECTSCENE_H
