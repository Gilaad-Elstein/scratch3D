//
// Created by gilaad on 2/10/20.
//

#include <math.h>
#include "JeepScene.h"

JeepScene::JeepScene() {
    meshList_.emplace_back(Scratch3d::Mesh::GetMeshFromObjectFile("Resources/Jeep_Renegade_2016.obj"));
    meshList_[0].texture = Scratch3d::Texture("../Resources/Jeep_Renegade_2016.jpg", 0, true, false);
    meshList_[0].invertRawXY();
    meshList_[0].rotateRaw(0, M_PI, 0);
}