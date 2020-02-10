//
// Created by gilaad on 1/24/20.
//

#include "AppWindow.h"
#include "Scene.h"
#include "Scenes/TestCubeScene.h"
#include "Scenes/AfricanHeadScene.h"
#include "Scenes/JeepScene.h"
#include <raylib.h>

const int WINDOWED_RESOLUTION_WIDTH = 640;
const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

bool fullscreen;

void ToggleFullscreenWrapper(bool STARTUP = False) {
    if (!STARTUP) fullscreen = !fullscreen;
    CloseWindow();
    if (fullscreen){
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
        InitWindow(FULLSCREEN_RESOLUTION_WIDTH, FULLSCREEN_RESOLUTION_HEIGHT, "scratch3D");
    }
    else{
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
    }
}

void AppWindow::run(){
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
    fullscreen = true;
    ToggleFullscreenWrapper(true);

    std::vector<Scene*> scenes;
    scenes.emplace_back(new TestCubeScene{});
    scenes.emplace_back(new AfricanHeadScene{});
    scenes.emplace_back(new JeepScene{});
    int sceneIndex = 0;

    while (!WindowShouldClose()){
        if(IsKeyPressed(KEY_M)) scenes[sceneIndex]->drawMesh = !scenes[sceneIndex]->drawMesh;
        if(IsKeyReleased(KEY_F)) ToggleFullscreenWrapper();
        if(IsKeyPressed(KEY_TAB)) sceneIndex = (sceneIndex+1)%(int)scenes.size();
        scenes[sceneIndex]->PlayFrame();
    }
    CloseWindow();
}