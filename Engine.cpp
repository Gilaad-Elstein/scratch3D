//
// Created by gilaad on 1/24/20.
//

#include "Engine.h"
#include "MeshObject.h"
#include <raylib.h>
#include <vector>
#include <tuple>
#include "Graphics.h"

const int WINDOWED_RESOLUTION_WIDTH = 640;
//const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int WINDOWED_RESOLUTION_HEIGHT = 640;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

Color MESHCOLOR = WHITE;
Color FILLCOLOR = LIGHTGRAY;

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
    bool drawMesh = true;

    std::vector<MeshObject> meshList;
//    meshList.emplace_back(MeshObject::GetTestCube(0.25));
    meshList.emplace_back(MeshObject::GetMeshFromObjectFile("Resources/head.obj"));
    float rotationRate = 0.25;
    float offsetRate = 0.3;
    float theta = 0;
    float offset = 2.0f;

    while (!WindowShouldClose()) {
        theta += rotationRate * GetFrameTime();
//        offset += offsetRate * GetFrameTime();
        ClearBackground(BLACK);
        BeginDrawing();
        for(auto& mesh : meshList){
            mesh.resetTransformations();
            mesh.rotate(theta, theta / 3, theta / 5);
            mesh.translate(0, 0, offset);
            mesh.transform(GetScreenWidth(), GetScreenHeight());
        }
        for(auto& mesh : meshList) {
            std::vector<TransformedFace> faces =  mesh.getTransformedFaces();
            for(auto const& face : faces){
                Graphics::drawFaceFilled(face, FILLCOLOR);
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