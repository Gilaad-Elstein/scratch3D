//
// Created by gilaad on 2/11/20.
//

#include "MeiPosedScene.h"

MeiPosedScene::MeiPosedScene() {
    meshList_.emplace_back(Scratch3d::Mesh::GetMeshFromObjectFile("Resources/Mei_Posed/rp_mei_posed_001_30k.obj"));
    meshList_[0].texture = Scratch3d::Texture("../Resources/TEST_TEXTURE.png", 0, false, false);//Mei_Posed/tex/rp_mei_posed_001_dif_2k.jpg");
    meshList_[0].invertRawXY();
//    meshList_[0].rotateRaw(0, M_PI, 0);
//    meshList_[0].translateRaw(0, 0.5f, -0.5f);
//    meshList_[0].texture.pixels.mirror('y');
}
