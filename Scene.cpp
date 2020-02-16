//
// Created by gilaad on 2/10/20.
//

#include "Scene.h"
#include "Graphics.h"
#include <raylib.h>
#include <limits>

void Scene::ResetZBuffer(){
    if(width != GetScreenWidth() || height != GetScreenHeight()){
        width = GetScreenWidth();
        height = GetScreenHeight();
    }
    delete zBuffer;
    zBuffer = new float[width * height];
    for (int i = 0; i < width * height; ++i) {
        zBuffer[i] = std::numeric_limits<float>::infinity();
    }
}

void Scene::PlayFrame() {
    ResetZBuffer();

    ClearBackground(BLACK);
    BeginDrawing();
    for(auto& mesh : meshList_){

        mesh.resetTransformations();
        Update();
        meshList_[0].translate(0, 0, 2);
        mesh.cullBackFaces();
        mesh.transform(width, height);
    }

    for(auto& mesh : meshList_) {
        std::vector<Scratch3d::TransformedFace> faces =  mesh.getTransformedFaces();
        for(auto & face : faces){
            if (face.texCoords.empty()) Graphics::drawFaceFilled(face, GRAY);
            else Graphics::drawFaceTextured(face, mesh.texture, zBuffer);
        }
        if (drawMesh){
            for(auto const& face : faces){
                Graphics::drawFaceLines(face, WHITE);
            }
        }
    }
    EndDrawing();
}

Scene::~Scene() {
    delete zBuffer;
}
