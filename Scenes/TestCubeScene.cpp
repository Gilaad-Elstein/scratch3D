//
// Created by gilaad on 2/10/20.
//

#include <raylib.h>
#include "TestCubeScene.h"
float rotationRate = 0.5;

TestCubeScene::TestCubeScene() {
    meshList_.emplace_back(Scratch3d::Mesh::GetTestCube(0.5));
    meshList_[0].texture = Scratch3d::Texture("Resources/TEST_TEXTURE.png");
}

void TestCubeScene::Update() {
    if (IsKeyDown(KEY_UP)) thetaX -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) thetaX += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) thetaY -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT)) thetaY += rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_Z)) thetaZ -= rotationRate * GetFrameTime();
    if (IsKeyDown(KEY_X)) thetaZ += rotationRate * GetFrameTime();

    meshList_[0].rotate(thetaX, thetaY, thetaZ);
    meshList_[0].translate(0, 0, 2);
}
