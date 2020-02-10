//
// Created by gilaad on 2/10/20.
//

#include "Scene.h"
#include "Graphics.h"
#include <raylib.h>

void Scene::PlayFrame() {

    ClearBackground(BLACK);
    BeginDrawing();
    for(auto& mesh : meshList_){
        mesh.resetTransformations();
        Update();
        mesh.cullBackFaces();
        mesh.transform(GetScreenWidth(), GetScreenHeight());
    }

    for(auto& mesh : meshList_) {
        std::vector<Scratch3d::TransformedFace> faces =  mesh.getTransformedFaces();
        for(auto & face : faces){
            if (face.texCoords.empty()) Graphics::drawFaceFilled(face, GRAY);
            else Graphics::drawFaceTextured(face, mesh.texture);
        }
        if (drawMesh){
            for(auto const& face : faces){
                Graphics::drawFaceLines(face, WHITE);
            }
        }
    }

    EndDrawing();

}

