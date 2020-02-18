//
// Created by gilaad on 2/10/20.
//

#include <raylib.h>
#include "RotatingObjectScene.h"

float rotationRate = 0.5f;
float cameraMoveRate = 0.5f;
float cameraTurnRate = 0.1f;

void RotatingObjectScene::Update() {
    if (IsKeyDown(KEY_UP)) thetaX -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) thetaX += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) thetaY -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT)) thetaY += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_Z)) thetaZ -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_X)) thetaZ += rotationRate * GetFrameTime();

    if (IsKeyDown(KEY_COMMA)) cameraPointAt.x += cameraTurnRate;
    if (IsKeyDown(KEY_PERIOD)) cameraPointAt.x -= cameraTurnRate;
    if (IsKeyDown(KEY_APOSTROPHE)) cameraPointAt.y += cameraTurnRate;
    if (IsKeyDown(KEY_SLASH)) cameraPointAt.y -= cameraTurnRate;

    if (IsKeyDown(KEY_P)) cameraPos.y += cameraMoveRate;
    if (IsKeyDown(KEY_SEMICOLON)) cameraPos.y -= cameraMoveRate;
    if (IsKeyDown(KEY_O)) cameraPos.z += cameraMoveRate;
    if (IsKeyDown(KEY_L)) cameraPos.z -= cameraMoveRate;

    meshList_[0].rotate(thetaX, thetaY, thetaZ);
}
