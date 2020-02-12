//
// Created by gilaad on 2/1/20.
//

#include <cmath>
#include "Graphics.h"


void Graphics::TintColor(Color &c, float dp) {
    c.r = static_cast<unsigned char>(static_cast<float>(c.r)*dp);
    c.g = static_cast<unsigned char>(static_cast<float>(c.g)*dp);
    c.b = static_cast<unsigned char>(static_cast<float>(c.b)*dp);

    if (c.r > 255) {c.r = 255;}
    else if (c.r < 0) {c.r = 0;}
    if (c.g > 255) {c.g = 255;}
    else if (c.g < 0) {c.g = 0;}
    if (c.b > 255) {c.b = 255;}
    else if (c.b < 0) {c.b = 0;}
}

void Graphics::DrawLine(Vec3 p1, Vec3 p2, Color &color) {

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
    for (int x = static_cast<int>(p1.x); x <= static_cast<int>(p2.x); x++) {
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
void Graphics::drawFaceLines(TransformedFace face, Color color) {
    for (int i = 0; i < face.vertices.size(); ++i) {
        DrawLine(face.vertices[i], face.vertices[(i+1)%face.vertices.size()], color);
    }
}

void Graphics::drawFaceFilled(TransformedFace& face, Color color) {
    if (face.vertices[1].y < face.vertices[0].y) std::swap(face.vertices[1], face.vertices[0]);
    if (face.vertices[2].y < face.vertices[0].y) std::swap(face.vertices[2], face.vertices[0]);
    if (face.vertices[2].y < face.vertices[1].y) std::swap(face.vertices[2], face.vertices[1]);

    int minY = face.vertices[0].y;
    int midY = face.vertices[1].y;
    int maxY = face.vertices[2].y;

    int dy1 = face.vertices[1].y - face.vertices[0].y;
    int dx1 = face.vertices[1].x - face.vertices[0].x;

    int dy2 =  face.vertices[2].y - face.vertices[0].y;
    int dx2 =  face.vertices[2].x - face.vertices[0].x;

    float dax_step = 0, dbx_step = 0;

    if (dy1) dax_step = dx1 / (float)abs(dy1);
    if (dy2) dbx_step = dx2 / (float)abs(dy2);

    if (dy1)
    {
        for (int i =  minY; i <= midY; i++)
        {
            int ax = face.vertices[0].x + (int)(i - face.vertices[0].y) * dax_step;
            int bx = face.vertices[0].x + (int)(i - face.vertices[0].y) * dbx_step;

            if (ax > bx) std::swap(ax, bx);

            for (int j = ax; j <= bx; j++)
            {
                DrawPixel(j, i, color);
            }
        }
    }

    dy1 = face.vertices[2].y - face.vertices[1].y;
    dx1 = face.vertices[2].x - face.vertices[1].x;

    if (dy1) dax_step = dx1 / (float)abs(dy1);
    if (dy2) dbx_step = dx2 / (float)abs(dy2);

    if (dy1)
    {
        for (int i = midY; i < maxY; i++)
        {
            int ax = face.vertices[1].x + (int)(i - face.vertices[1].y) * dax_step;
            int bx = face.vertices[0].x + (int)(i - face.vertices[0].y) * dbx_step;
            if (i == midY) ax = face.vertices[1].x;

            if (ax > bx) std::swap(ax, bx);

            for (int j = ax; j <= bx; j++)
            {
                DrawPixel(j, i, color);
            }
        }
    }
}

void Graphics::drawFaceTextured(TransformedFace &face, Scratch3d::Texture &texture, float *zBuffer) {
    if (face.vertices[1].y < face.vertices[0].y) {
        std::swap(face.vertices[1], face.vertices[0]);
        std::swap(face.normals[1], face.normals[0]);
        std::swap(face.texCoords[1], face.texCoords[0]);
    }
    if (face.vertices[2].y < face.vertices[0].y){
        std::swap(face.vertices[2], face.vertices[0]);
        std::swap(face.normals[2], face.normals[0]);
        std::swap(face.texCoords[2], face.texCoords[0]);
    }
    if (face.vertices[2].y < face.vertices[1].y){
        std::swap(face.vertices[2], face.vertices[1]);
        std::swap(face.normals[2], face.normals[1]);
        std::swap(face.texCoords[2], face.texCoords[1]);
    }

    int minY = face.vertices[0].y;
    int midY = face.vertices[1].y;
    int maxY = face.vertices[2].y;

    int dy1 = face.vertices[1].y - face.vertices[0].y;
    int dx1 = face.vertices[1].x - face.vertices[0].x;
    float ddp1 = Vec3{0, 0, -1}.DotProduct(face.normals[1]) - Vec3{0, 0, -1}.DotProduct(face.normals[0]);
    float dv1 = face.texCoords[1].v - face.texCoords[0].v;
    float du1 = face.texCoords[1].u - face.texCoords[0].u;
    float dw1 = face.texCoords[1].w - face.texCoords[0].w;

    int dy2 =  face.vertices[2].y - face.vertices[0].y;
    int dx2 =  face.vertices[2].x - face.vertices[0].x;
    float ddp2 = Vec3{0, 0, -1}.DotProduct(face.normals[2]) - Vec3{0, 0, -1}.DotProduct(face.normals[0]);
    float dv2 = face.texCoords[2].v - face.texCoords[0].v;
    float du2 = face.texCoords[2].u - face.texCoords[0].u;
    float dw2 = face.texCoords[2].w = face.texCoords[0].w;

    float tex_u, tex_v, tex_w;

    float dax_step = 0, dbx_step = 0,
            du1_step = 0, dv1_step = 0,
            du2_step = 0, dv2_step = 0,
            dw1_step=0, dw2_step=0;


    if (dy1) dax_step = dx1 / (float)abs(dy1);
    if (dy2) dbx_step = dx2 / (float)abs(dy2);

    if (dy1) du1_step = du1 / (float)abs(dy1);
    if (dy1) dv1_step = dv1 / (float)abs(dy1);
    if (dy1) dw1_step = dw1 / (float)abs(dy1);

    if (dy2) du2_step = du2 / (float)abs(dy2);
    if (dy2) dv2_step = dv2 / (float)abs(dy2);
    if (dy2) dw2_step = dw2 / (float)abs(dy2);

    float dz1 = face.vertices[1].z - face.vertices[0].z;
    float dz2 = face.vertices[2].z - face.vertices[0].z;

    if (dy1)
    {
        for (int i =  minY; i <= midY; i++)
        {
            int ax = face.vertices[0].x + (int)(i - face.vertices[0].y) * dax_step;
            int bx = face.vertices[0].x + (int)(i - face.vertices[0].y) * dbx_step;
            float az = face.vertices[0].z + dz1 * (i - minY)/(float)abs((dy1));
            float bz = face.vertices[0].z + dz2 * (i - minY)/(float)abs((dy1));
            float ad = Vec3{0, 0, -1}.DotProduct(face.normals[0]) + ddp1 * (i - minY)/(float)abs((dy1));
            float bd = Vec3{0, 0, -1}.DotProduct(face.normals[0]) + ddp2 * (i - minY)/(float)abs((dy1));

            float tex_su = face.texCoords[0].u + (float)(i - face.vertices[0].y) * du1_step;
            float tex_sv = face.texCoords[0].v + (float)(i - face.vertices[0].y) * dv1_step;
            float tex_sw = face.texCoords[0].w + (float)(i - face.vertices[0].y) * dw1_step;

            float tex_eu = face.texCoords[0].u + (float)(i - face.vertices[0].y) * du2_step;
            float tex_ev = face.texCoords[0].v + (float)(i - face.vertices[0].y) * dv2_step;
            float tex_ew = face.texCoords[0].w + (float)(i - face.vertices[0].y) * dw2_step;

            if (ax > bx){
                std::swap(ax, bx);
                std::swap(az, bz);
                std::swap(ad, bd);
                std::swap(tex_su, tex_eu);
                std::swap(tex_sv, tex_ev);
                std::swap(tex_sw, tex_ew);
            }

            float texStep = 1.0f / ((float)(bx - ax));
            float t = 0.0f;

            for (int j = ax; j <= bx; j++)
            {
                tex_u = (1.0f - t) * tex_su + t * tex_eu;
                tex_v = (1.0f - t) * tex_sv + t * tex_ev;
                tex_w = (1.0f - t) * tex_sw + t * tex_ew;
                tex_u = std::min(tex_u, 1.0f);
                tex_v = std::min(tex_v, 1.0f);
                tex_w = std::min(tex_w, 1.0f);
                tex_u = std::max(tex_u, 0.0f);
                tex_v = std::max(tex_v, 0.0f);
                tex_w = std::max(tex_w, 0.0f);

                float z = az;
                if (bx - ax) z += (bz - az) * (j - ax) / float(bx - ax);
                float dp = ad;
                if (bx - ax) dp += (bd - ad) * (j - ax) / float(bx - ax);

                int zBufferIndex = j + i * GetScreenWidth();
                if(zBufferIndex < GetScreenWidth() * GetScreenHeight() && z < zBuffer[zBufferIndex])
                {
                    zBuffer[zBufferIndex] = z;
                    Color color = texture.Sample(tex_u, tex_v);
                    TintColor(color, 1);
                    DrawPixel(j, i, color);
                }
                t += texStep;
            }
        }
    }

    dy1 = face.vertices[2].y - face.vertices[1].y;
    dx1 = face.vertices[2].x - face.vertices[1].x;
    dv1 = face.texCoords[2].v - face.texCoords[1].v;
    du1 = face.texCoords[2].u - face.texCoords[1].u;
    dw1 = face.texCoords[2].w - face.texCoords[1].w;

    if (dy1) dax_step = dx1 / (float)abs(dy1);
    if (dy2) dbx_step = dx2 / (float)abs(dy2);

    if (dy1) du1_step = du1 / (float)abs(dy1);
    if (dy1) dv1_step = dv1 / (float)abs(dy1);
    if (dy1) dw1_step = dw1 / (float)abs(dy1);

    dz1 = face.vertices[2].z - face.vertices[1].z;

    if (dy1){
        for (int i = midY; i < maxY; i++)
        {
            int ax = face.vertices[1].x + (int)(i - face.vertices[1].y) * dax_step;
            int bx = face.vertices[0].x + (int)(i - face.vertices[0].y) * dbx_step;
            float az = face.vertices[1].z + dz1 * (i - midY)/(float)abs((dy1));
            float bz = face.vertices[0].z + dz2 * (i - midY)/(float)abs((dy1));

            float tex_su = face.texCoords[1].u + (float)(i - face.vertices[1].y) * du1_step;
            float tex_sv = face.texCoords[1].v + (float)(i - face.vertices[1].y) * dv1_step;
            float tex_sw = face.texCoords[1].w + (float)(i - face.vertices[1].y) * dw1_step;

            float tex_eu = face.texCoords[0].u + (float)(i - face.vertices[0].y) * du2_step;
            float tex_ev = face.texCoords[0].v + (float)(i - face.vertices[0].y) * dv2_step;
            float tex_ew = face.texCoords[0].w + (float)(i - face.vertices[0].y) * dw2_step;

            if (ax > bx) {
                std::swap(ax, bx);
                std::swap(az, bz);
                std::swap(tex_su, tex_eu);
                std::swap(tex_sv, tex_ev);
                std::swap(tex_sw, tex_ew);
            }
            tex_u = tex_su;
            tex_v = tex_sv;
            tex_w = tex_sw;

            float tstep = 1.0f / ((float)(bx - ax));
            float t = 0.0f;

            for (int j = ax; j <= bx; j++)
            {
            tex_u = (1.0f - t) * tex_su + t * tex_eu;
            tex_v = (1.0f - t) * tex_sv + t * tex_ev;
            tex_w = (1.0f - t) * tex_sw + t * tex_ew;
            tex_u = std::min(tex_u, 1.0f);
            tex_v = std::min(tex_v, 1.0f);
            tex_w = std::min(tex_w, 1.0f);
            tex_u = std::max(tex_u, 0.0f);
            tex_v = std::max(tex_v, 0.0f);
            tex_w = std::max(tex_w, 0.0f);

            float z = az;
            if (bx - ax) z += (bz - az) * (j - ax) / float(bx - ax);
            int zBufferIndex = j + i * GetScreenWidth();
            if(zBufferIndex < GetScreenWidth() * GetScreenHeight() && z < zBuffer[zBufferIndex])
            {
                zBuffer[zBufferIndex] = z;
                Color color = texture.Sample(tex_u, tex_v);
                TintColor(color, 1);
                DrawPixel(j, i, color);
            }
                t += tstep;
            }
        }
    }
}