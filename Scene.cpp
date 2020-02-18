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

    //camera derivs:
    Vec3 cameraForward = cameraPos - cameraPointAt;
    cameraForward.Normalise();
    Vec3 cameraRight = cameraForward.CrossProduct(cameraUp);
    cameraRight.Normalise();
    Vec3 cameraV = cameraRight.CrossProduct(cameraForward);

    Matrix4x4 matCamera;
    matCamera.m[0][0] = cameraRight.x;
    matCamera.m[0][1] = cameraRight.y;
    matCamera.m[0][2] = cameraRight.z;
    matCamera.m[1][0] = cameraV.x;
    matCamera.m[1][1] = cameraV.y;
    matCamera.m[1][2] = cameraV.z;
    matCamera.m[2][0] = cameraForward.x;
    matCamera.m[2][1] = cameraForward.y;
    matCamera.m[2][2] = cameraForward.z;
    matCamera.m[3][0] = -cameraPos.DotProduct(cameraRight);
    matCamera.m[3][1] = -cameraPos.DotProduct(cameraV);
    matCamera.m[3][2] = -cameraPos.DotProduct(cameraForward);
    matCamera.m[3][3] = 1.0f;

    ClearBackground(BLACK);
    BeginDrawing();
    for(auto& mesh : meshList_){

        mesh.resetTransformations();
        Update();
        mesh.translate(0,0,3);
        mesh.cullBackFaces();
        mesh.transform(matCamera);
        mesh.flatTransform(GetScreenWidth(), GetScreenHeight());
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
