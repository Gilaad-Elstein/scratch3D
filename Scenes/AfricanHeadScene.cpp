//
// Created by gilaad on 2/10/20.
//

#include "AfricanHeadScene.h"

AfricanHeadScene::AfricanHeadScene() {
    meshList_.emplace_back(Scratch3d::Mesh::GetMeshFromObjectFile("../Resources/african_head.obj"));
    meshList_[0].texture = Scratch3d::Texture("../Resources/head.tga");
    meshList_[0].texture.pixels.rotate(180);
    meshList_[0].invertRawXY();
    meshList_[0].rotateRaw(0, M_PI, 0);
}