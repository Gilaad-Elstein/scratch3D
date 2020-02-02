//
// Created by gilaad on 2/1/20.
//

#include <cmath>
#include "Graphics.h"

Vec3 interpolate(const Vec3& src, const Vec3& dst,float alpha )
{
    return src + (dst - src) * alpha;
}
void drawFlatTopTriangle(Vec3 p0, Vec3 p1, Vec3 p2, Color color){
    //slopes
    float m0 = (p2.x - p0.x) / (p2.y - p0.y);
    float m1 = (p2.x - p1.x) / (p2.y - p1.y);
    //to pixel space
    int minY = (int)std::ceil(p0.y - 0.5f);
    int maxY = (int)std::ceil(p2.y - 0.5f);
    for(int y = minY; y < maxY; ++y) {
        //to pixel space
        float fMinX = m0 * ((float)y + 0.5f - p0.y) + p0.x;
        float fMaxX = m1 * ((float)y + 0.5f - p1.y) + p1.x;
        int minX = (int)std::ceil(fMinX - 0.5f );
        int maxX = (int)std::ceil(fMaxX - 0.5f );
        for (int x = minX; x < maxX; ++x) {
            DrawPixel(x, y, color);
        }
    }
}
void drawFlatBottomTriangle(Vec3 p0, Vec3 p1, Vec3 p2, Color color){
    //slopes
    float m0 = (p1.x - p0.x) / (p1.y - p0.y);
    float m1 = (p2.x - p0.x) / (p2.y - p0.y);
    //to pixel space
    int minY = (int)std::ceil(p0.y - 0.5f);
    int maxY = (int)std::ceil(p2.y - 0.5f);
    for(int y = minY; y < maxY; ++y) {
        //to pixel space
        float fMinX = m0 * ((float)y + 0.5f - p0.y) + p0.x;
        float fMaxX = m1 * ((float)y + 0.5f - p0.y) + p0.x;
        int minX = (int)std::ceil(fMinX - 0.5f );
        int maxX = (int)std::ceil(fMaxX - 0.5f );
        for (int x = minX; x < maxX; ++x) {
            DrawPixel(x, y, color);
        }
    }
}

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
    // get pointers so we can use std::swap for sorting
    const Vec3* pv0 = &face.vertices[0];
    const Vec3* pv1 = &face.vertices[1];
    const Vec3* pv2 = &face.vertices[2];

    // sort by y
    if( pv1->y < pv0->y ) std::swap( pv0,pv1 );
    if( pv2->y < pv1->y ) std::swap( pv1,pv2 );
    if( pv1->y < pv0->y ) std::swap( pv0,pv1 );

    if( pv0->y == pv1->y ) // natural flat top
    {
        // sort by x
        if( pv1->x < pv0->x ) std::swap(pv0,pv1);
        drawFlatTopTriangle(*pv0,*pv1,*pv2, color);
    }
    else if( pv1->y == pv2->y ) // flat bottom
    {
        // sort by x
        if( pv2->x < pv1->x ) std::swap( pv1,pv2 );
        drawFlatBottomTriangle(*pv0,*pv1,*pv2, color);
    }
    else // none flat, split to flat triangles
    {
        // splitting ratio and interpolation
        const float ratio =
                (pv1->y - pv0->y) /
                (pv2->y - pv0->y);
        Vec3 vi = interpolate(*pv0, *pv2, ratio);

        if( pv1->x < vi.x ) // right heavy triangle
        {
            drawFlatBottomTriangle(*pv0, *pv1, vi, color);
            drawFlatTopTriangle(*pv1, vi, *pv2, color);
        }
        else // left heavy triangle
        {
            drawFlatBottomTriangle(*pv0, vi, *pv1, color);
            drawFlatTopTriangle(vi, *pv1, *pv2, color);}
    }
}