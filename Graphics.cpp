//
// Created by gilaad on 2/1/20.
//

#include <cmath>
#include "Graphics.h"

Vec3d interpolate(const Vec3d& src,const Vec3d& dst,float alpha)
{
    return src + (dst - src) * alpha;
}
// does processing common to both flat top and flat bottom tris
// scan over triangle in screen space, interpolate attributes,
// depth cull, invoke ps and write pixel to screen
void DrawFlatTriangle(const Vec3d& it0,
                      const Vec3d& it1,
                      const Vec3d& it2,
                      const Vec3d& dv0,
                      const Vec3d& dv1,
                      Vec3d itEdge1,
                      Color color)
{
    // create edge interpolant for left edge (always v0)
    auto itEdge0 = it0;

    // calculate start and end scan-lines
    const int yStart = std::max( (int)ceilf( it0.y - 0.5f ),0 );
    const int yEnd = std::min( (int)ceilf( it2.y - 0.5f ),GetScreenHeight() - 1 ); // the scanline AFTER the last line drawn

    // do interpolant pre-step
    itEdge0 += dv0 * (float( yStart ) + 0.5f - it0.y);
    itEdge1 += dv1 * (float( yStart ) + 0.5f - it0.y);

    for( int y = yStart; y < yEnd; y++,itEdge0 += dv0,itEdge1 += dv1 )
    {
        // calculate start and end pixels
        const int xStart = std::max( (int)ceilf( itEdge0.x - 0.5f ),0 );
        const int xEnd = std::min( (int)ceilf( itEdge1.x - 0.5f ),GetScreenWidth() - 1 ); // the pixel AFTER the last pixel drawn

        // create scan-line interpolant start point
        // (some waste for interpolating x,y,z, but makes life easier not having
        //  to split them off, and z will be needed in the future anyways...)
        auto iLine = itEdge0;

        // calculate delta scanline interpolant / dx
        const float dx = itEdge1.x - itEdge0.x;
        const auto diLine = (itEdge1 - iLine) / dx;

        // prestep scan-line interpolant
        iLine += diLine * (float( xStart ) + 0.5f - itEdge0.x);

        for( int x = xStart; x < xEnd; x++,iLine += diLine )
        {
            DrawPixel(x, y, color);
        }
    }
}
void DrawFlatTopTriangle(const Vec3d& it0,
                         const Vec3d& it1,
                         const Vec3d& it2,
                         Color color)
{
    // calculate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.y - it0.y;
    const auto dit0 = (it2 - it0) / delta_y;
    const auto dit1 = (it2 - it1) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it1;

    // call the flat triangle render routine
    DrawFlatTriangle(it0,it1,it2,dit0,dit1,itEdge1, color);
}
// does flat *BOTTOM* tri-specific calculations and calls DrawFlatTriangle
void DrawFlatBottomTriangle(const Vec3d& it0,
                            const Vec3d& it1,
                            const Vec3d& it2,
                            Color color)
{
    // calulcate dVertex / dy
    // change in interpolant for every 1 change in y
    const float delta_y = it2.y - it0.y;
    const auto dit0 = (it1 - it0) / delta_y;
    const auto dit1 = (it2 - it0) / delta_y;

    // create right edge interpolant
    auto itEdge1 = it0;

    // call the flat triangle render routine
    DrawFlatTriangle(it0,it1,it2,dit0,dit1,itEdge1, color);
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
void Graphics::DrawLine(Vec3d p1, Vec3d p2, Color &color) {
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
void Graphics::drawFaceFilled(TransformedFace face, Color color) {
    if (face.vertices.size() != 3) throw std::runtime_error("Graphics::drawFaceFilled received 3+ nGone but triangulation not impl.");

    const Vec3d* pv0 = &face.vertices[0];
    const Vec3d* pv1 = &face.vertices[1];
    const Vec3d* pv2 = &face.vertices[2];

    // sorting vertices by y
    if( pv1->y < pv0->y ) std::swap(pv0,pv1);
    if( pv2->y < pv1->y ) std::swap(pv1,pv2);
    if( pv1->y < pv0->y ) std::swap(pv0,pv1);

    if( pv0->y == pv1->y ) // natural flat top
    {
        // sorting top vertices by x
        if( pv1->x < pv0->x ) std::swap(pv0,pv1);

        DrawFlatTopTriangle(*pv0,*pv1,*pv2, color);
    }
    else if( pv1->y == pv2->y ) // natural flat bottom
    {
        // sorting bottom vertices by x
        if( pv2->x < pv1->x ) std::swap( pv1,pv2 );

        DrawFlatBottomTriangle(*pv0,*pv1,*pv2, color);
    }
    else // general triangle
    {
        // find splitting vertex interpolant
        const float alphaSplit =
                (pv1->y - pv0->y) /
                (pv2->y - pv0->y);
        const auto vi = interpolate( *pv0,*pv2,alphaSplit );

        if( pv1->x < vi.x ) // major right NOLINT(bugprone-branch-clone)
        {
            DrawFlatBottomTriangle(*pv0,*pv1,vi, color);
            DrawFlatTopTriangle(*pv1,vi,*pv2, color);
        }
        else // major left
        {
            DrawFlatBottomTriangle(*pv0,vi,*pv1, color);
            DrawFlatTopTriangle(vi,*pv1,*pv2, color);
        }
    }
}