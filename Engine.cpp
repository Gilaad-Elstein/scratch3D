//
// Created by gilaad on 1/24/20.
//

#include "Engine.h"
#include "Mesh.h"
#include <raylib.h>
#include <vector>
#include <tuple>
#include "Graphics.h"
#include "Texture.h"

using Scratch3d::TransformedFace;

float MESH_VIEW_SIZE_FACTOR = 0.25f;

const int WINDOWED_RESOLUTION_WIDTH = 640;
//const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int WINDOWED_RESOLUTION_HEIGHT = 640;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

Color MESHCOLOR = WHITE;
Color FILLCOLOR = GRAY;

std::string DEBUG_MSG;
bool fullscreen;

void ToggleFullscreenWrapper() {
    fullscreen = !fullscreen;
    CloseWindow();
    if (fullscreen){
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
        InitWindow(FULLSCREEN_RESOLUTION_WIDTH, FULLSCREEN_RESOLUTION_HEIGHT, "scratch3D");
    }
    else{
        SetConfigFlags(FLAG_VSYNC_HINT);
        InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
    }
}

void Engine::run(){
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
    fullscreen = true;
    bool drawMesh = false;

    std::vector<Scratch3d::Mesh> meshList;
    std::vector<Scratch3d::Texture> texList;
//    meshList.emplace_back(Scratch3d::Mesh::GetTestCube(0.65));
//    texList.emplace_back(Scratch3d::Texture("Resources/TEST_TEXTURE.png"));
//    texList.emplace_back(Scratch3d::Texture("Resources/simpleTexture.jpg"));
    meshList.emplace_back(Scratch3d::Mesh::GetMeshFromObjectFile("Resources/head.obj"));
    texList.emplace_back(Scratch3d::Texture("Resources/head_diffuse.tga"));
    meshList[0].invertRawXY();

    float rotationRate = 0.5;
    float offsetRate = 0.1;
    float thetaX = 0;
    float thetaY = M_PI;
    float thetaZ = 0;
    float offset = 2.0f;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_UP)) thetaX -= rotationRate * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) thetaX += rotationRate * GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) thetaY -= rotationRate * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) thetaY += rotationRate * GetFrameTime();
        if (IsKeyDown(KEY_Z)) thetaZ -= rotationRate * GetFrameTime();
        if (IsKeyDown(KEY_X)) thetaZ += rotationRate * GetFrameTime();
        ClearBackground(BLACK);
        BeginDrawing();
        for(auto& mesh : meshList){
            mesh.resetTransformations();
            mesh.rotate(thetaX, thetaY, thetaZ);
            mesh.translate(0, 0, 2);
            mesh.cullBackFaces();
            mesh.transform(GetScreenWidth(), GetScreenHeight());
        }

        for(auto& mesh : meshList) {
            std::vector<TransformedFace> faces =  mesh.getTransformedFaces();
            for(auto & face : faces){
                if (face.texCoords.empty()) Graphics::drawFaceFilled(face, FILLCOLOR);
                else Graphics::drawFaceTextured(face, texList[0]);
            }
            if (drawMesh){
                for(auto const& face : faces){
                    Graphics::drawFaceLines(face, MESHCOLOR);
                }
            }
        }

        DrawText(DEBUG_MSG.c_str(), 100, 100, 16, WHITE);
        if(IsKeyPressed(KEY_M)) drawMesh = !drawMesh;
        EndDrawing();
    }
    CloseWindow();
}