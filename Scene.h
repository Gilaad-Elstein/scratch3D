//
// Created by gilaad on 2/10/20.
//

#ifndef SCRATCH3D_SCENE_H
#define SCRATCH3D_SCENE_H

#include "Mesh.h"
#include "structs/Texture.h"

class Scene {
protected:
    std::vector<Scratch3d::Mesh> meshList_;
public:
    bool drawMesh = false;
    void PlayFrame();
    virtual void Update() = 0;
};


#endif //SCRATCH3D_SCENE_H
