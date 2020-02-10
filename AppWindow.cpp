//
// Created by gilaad on 1/24/20.
//

#include "AppWindow.h"
#include "Scene.h"
#include "Scenes/TestCubeScene.h"
#include <raylib.h>

const int WINDOWED_RESOLUTION_WIDTH = 640;
//const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int WINDOWED_RESOLUTION_HEIGHT = 640;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

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

void AppWindow::run(){
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
    fullscreen = true;

    TestCubeScene scene{};

    while (!WindowShouldClose()){
        if(IsKeyPressed(KEY_M)) scene.drawMesh = !scene.drawMesh;
        scene.PlayFrame();
    }
    CloseWindow();
}