//
// Created by gilaad on 1/24/20.
//

#include "Engine.h"
#include "Vec3d.h"
#include "ObjectMesh.h"
#include <raylib.h>
#include <vector>
#include <tuple>
#include <algorithm>

const int WINDOWED_RESOLUTION_WIDTH = 640;
const int WINDOWED_RESOLUTION_HEIGHT = 480;
const int FULLSCREEN_RESOLUTION_WIDTH = 1440;
const int FULLSCREEN_RESOLUTION_HEIGHT = 900;

Color MESHCOLOR = WHITE;
Color FILLCOLOR = LIGHTGRAY;

std::string DEBUG_MSG;
bool fullscreen;

void TintColor(Color &c, double dp) {
    c.r = static_cast<unsigned char>(c.r*dp);
    c.g = static_cast<unsigned char>(c.g*dp);
    c.b = static_cast<unsigned char>(c.b*dp);

    if (c.r > 255) {c.r = 255;}
    else if (c.r < 0) {c.r = 0;}
    if (c.g > 255) {c.g = 255;}
    else if (c.g < 0) {c.g = 0;}
    if (c.b > 255) {c.b = 255;}
    else if (c.b < 0) {c.b = 0;}
}
void DrawLine(Vec3d p1, Vec3d p2, Color& color){
    bool steep = false;
    //invert steep lines
    if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y)) {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }
    //draw from left to right
    if (p1.x > p2.x) {
        std::swap(p1.x, p2.x);
        std::swap(p1.y, p2.y);
    }

    int dx = static_cast<int>(p2.x) - static_cast<int>(p1.x);
    int dy = static_cast<int>(p2.y) - static_cast<int>(p1.y);
    int dError2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = static_cast<int>(p1.y);
    for (int x = static_cast<int>(p1.x); x <= p2.x; x++) {
        if (steep) {
            DrawPixel(y, x, color);
        } else {
            DrawPixel(x, y, color);
        } //when error2 accumulates beyond dx increment y and update error2 accordingly
        error2 += dError2;
        if (error2 > dx) {
            y += (p2.y>p1.y?1:-1);
            error2 -= dx*2;
        }
    }
}
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
void DrawPolygonLines(Polygon &poly){
    for (int i = 0; i < poly.points.size(); ++i) {
        DrawLine(poly.points[i],
                 poly.points[(i+1)%poly.points.size()],
                  MESHCOLOR);
    }
}
void DrawPolyFilled(Polygon &poly, Color &color, double* &zBuffer) {
    std::tuple<int, int> min_max_y = poly.GetMinMaxYVals();
    int min_y = std::max(0, std::get<0>(min_max_y));
    int max_y = std::min(GetScreenHeight(), std::get<1>(min_max_y));
    for (int y = min_y; y <= max_y; ++y) {
        std::vector<double> nodes = poly.GetYLineNodes(y);
        if (nodes.empty()) {continue;}
        int minX = static_cast<int>(nodes[0]), maxX = static_cast<int>(nodes[1]);
        std::tuple<double, double> leftRightZValues = poly.GetZValues(y);
        double zLeft = std::get<0>(leftRightZValues), zRight = std::get<1>(leftRightZValues);
        for (int x = minX; x <= maxX; ++x) {
            int numNode = 0;
            if (x > nodes[nodes.size() - 1]){ break;}
            while (x > nodes[numNode]){ numNode++; }
                double localZ = zLeft +
                               (zRight - zLeft) *
                                static_cast<double>(x -minX) /
                                (maxX - minX);
                if (localZ < zBuffer[y * GetScreenWidth() + x]) continue;
                zBuffer[y * GetScreenWidth() + x] = localZ;
                DrawPixel(x, y, color);
        }
    }
}

void Engine::Run() {
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(FULLSCREEN_RESOLUTION_WIDTH, FULLSCREEN_RESOLUTION_HEIGHT, "scratch3D");
    fullscreen = true;
    bool drawMesh = false;
    Vec3d vLightDirection = Vec3d{0.0, 0.0, 1.0 }.GetNormal();

    std::vector<ObjectMesh> meshList;
    meshList.emplace_back(ObjectMesh::GetMeshFromObjectFile("Resources/head.obj"));
//    meshList.emplace_back(ObjectMesh::GetMeshFromObjectFile("Resources/spaceship.obj"));
//    meshList.emplace_back(ObjectMesh::GetTestCube(10.0));

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        int zBufferSize = GetScreenWidth()*GetScreenHeight();
        auto* zBuffer = new double[zBufferSize];
        for (int i = 0; i < zBufferSize; ++i) {
            zBuffer[i] = -std::numeric_limits<double>::infinity();
        }

        BeginDrawing();
        for (auto &mesh : meshList) {
            for (auto &poly : mesh.polygons) {
                // Illumination and backface culling
                Vec3d normal = poly.GetNormalizedNormal();
                double dp = vLightDirection.DotProduct(normal);
                if (dp < 0) continue;

                dp = std::max(0.1, dp);
                Color color = FILLCOLOR;
                TintColor(color, dp);

                Polygon polyManipulated = poly.Clone();

                polyManipulated.InvertXY();
                polyManipulated.ScaleToScreenSpace(GetScreenWidth(), GetScreenHeight());
                DrawPolyFilled(polyManipulated, color, zBuffer);
                if (drawMesh) DrawPolygonLines(polyManipulated);
            }
        }
        EndDrawing();

        delete [] zBuffer;

        if(IsKeyReleased(KEY_F)) ToggleFullscreenWrapper();
        if(IsKeyPressed(KEY_M)) drawMesh = !drawMesh;
    }
}

void Engine::TextureMapViewer(){


    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_UNDECORATED);
    InitWindow(FULLSCREEN_RESOLUTION_WIDTH, FULLSCREEN_RESOLUTION_HEIGHT, "scratch3D");
    fullscreen = true;
    bool drawMesh = true;


    Image iTexture = LoadImage("Resources/head_diffuse.tga");
    Texture2D texture = LoadTextureFromImage(iTexture);
    UnloadImage(iTexture);

    ObjectMesh head = ObjectMesh::GetMeshFromObjectFile("Resources/head.obj");

    while (!WindowShouldClose()) {

        ClearBackground(BLACK);
        BeginDrawing();

        DrawTexture(texture,  GetScreenWidth()/2 - texture.width/2, 0, WHITE);

        if (drawMesh){
            for(auto& poly : head.polygons){
                Polygon tPoly = poly.GetTexturePolygon();
                tPoly.FlipNormalizedPolyVertically();
                tPoly.Scale2D(texture.width, texture.height);
                tPoly.Translate2D(GetScreenWidth()/2.0 - texture.width/2.0, 0);
                DrawPolygonLines(tPoly);
            }
        }

        EndDrawing();

        if(IsKeyReleased(KEY_F)) ToggleFullscreenWrapper();
        if(IsKeyPressed(KEY_M)) drawMesh = !drawMesh;
        DrawText(DEBUG_MSG.c_str(), 100, 100, 16, WHITE);
    }
    UnloadTexture(texture);
}