//
// Created by gilaad on 2/10/20.
//

#include "TestCubeScene.h"

TestCubeScene::TestCubeScene() {
    meshList_.emplace_back(Scratch3d::Mesh::GetTestCube(0.5));
    meshList_[0].texture = Scratch3d::Texture("Resources/TEST_TEXTURE.png", 0, false, false);
}