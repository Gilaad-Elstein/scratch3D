//
// Created by gilaad on 2/10/20.
//

#ifndef SCRATCH3D_SCENE_H
#define SCRATCH3D_SCENE_H

#include "Mesh.h"
#include "structs/Texture.h"

class Scene {
protected:
    //camera controls
    Vec3 cameraPos{0, 0, -1};
    Vec3 cameraPointAt{0, 0, 1};
    Vec3 cameraUp{0, 1, 0};

    std::vector<Scratch3d::Mesh> meshList_;
    float* zBuffer = NULL;
    int width = 0, height = 0;

    void ResetZBuffer();
    ~Scene();


public:
    bool drawMesh = false;
    void PlayFrame();
    virtual void Update() = 0;

};


#endif //SCRATCH3D_SCENE_H
