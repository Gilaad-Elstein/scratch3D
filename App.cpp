//
// Created by gilaad on 1/24/20.
//

#include "App.h"
#include "Scene.h"
#include "Scenes/TestCubeScene.h"
#include "Scenes/AfricanHeadScene.h"
#include "Scenes/JeepScene.h"
#include "Scenes/MeiPosedScene.h"
#include <raylib.h>

const int WINDOWED_RESOLUTION_WIDTH = 640;
const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

bool fullscreen;
bool activeWindow = false;

void InitAppWindow(bool requestedFullscreen){
    if (activeWindow) CloseWindow();
    activeWindow = false;
    SetTargetFPS(30);
    if (requestedFullscreen){
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
        InitWindow(FULLSCREEN_RESOLUTION_WIDTH, FULLSCREEN_RESOLUTION_HEIGHT, "scratch3D");
        fullscreen = true;
    }
    else{
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
        InitWindow(WINDOWED_RESOLUTION_WIDTH, WINDOWED_RESOLUTION_HEIGHT, "scratch3D");
        fullscreen = false;
    }
    activeWindow = true;
}

void App::run(){
    InitAppWindow(true);

    std::vector<Scene*> scenes;
    scenes.emplace_back(new TestCubeScene{});
    scenes.emplace_back(new AfricanHeadScene{});
    scenes.emplace_back(new JeepScene{});
    int sceneIndex = 0;

    while (!WindowShouldClose()){
        if(IsKeyPressed(KEY_M)) scenes[sceneIndex]->drawMesh = !scenes[sceneIndex]->drawMesh;
        if(IsKeyReleased(KEY_F)) InitAppWindow(!fullscreen);
        if(IsKeyPressed(KEY_TAB)) sceneIndex = (sceneIndex+1)%(int)scenes.size();
        scenes[sceneIndex]->PlayFrame();
    }
    CloseWindow();
}