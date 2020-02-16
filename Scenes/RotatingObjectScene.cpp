//
// Created by gilaad on 2/10/20.
//

#include <raylib.h>
#include "RotatingObjectScene.h"

float rotationRate = 0.5;

void RotatingObjectScene::Update() {
    if (IsKeyDown(KEY_UP)) thetaX -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) thetaX += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) thetaY -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT)) thetaY += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_Z)) thetaZ -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_X)) thetaZ += rotationRate * GetFrameTime();

    meshList_[0].rotate(thetaX, thetaY, thetaZ);
}
