//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_MESH_H
#define SCRATCH3D_MESH_H


#include <vector>
#include <sstream>
#include "structs/Vec3.h"
#include "structs/Vec2.h"
#include "structs/Texture.h"

namespace Scratch3d{
    struct Face{
        Face() = default;
        Face(size_t v1, size_t v2, size_t v3);
        Face(size_t v1, size_t v2, size_t v3, std::vector<Vec2> texCoords);
        Face(std::vector<size_t> indices, std::vector<size_t> normalIndices, std::vector<Vec2> texCoords);
        std::vector<size_t> iVertices;
        std::vector<Vec2> texCoords;
        std::vector<size_t> iNormals;
    };

    struct TransformedFace{
        std::vector<Vec3> vertices;
        std::vector<Vec2> texCoords;
        std::vector<Vec3> normals;
    };

    class Mesh {
        Mesh() {}

        std::vector<Vec3> rawVertices;
        std::vector<Vec3> manipulatedVertices;
        std::vector<Face> facesIndexLists;
        std::vector<bool> visibleFaces;
        std::vector<Vec3> rawNormals;
        std::vector<Vec3> manipulatedNormals;

    public:
        void resetTransformations();
        void translate(float x, float y, float z);
        void translateRaw(float x, float y, float z);
        void rotate(float x, float y, float z);
        void rotateRaw(float x, float y, float z);
        void transform(int w, int h);
        void cullBackFaces();
        std::vector<TransformedFace> getTransformedFaces();
        void invertRawXY();

        static Mesh GetTestCube(float size);
        static Mesh GetMeshFromObjectFile(const std::string &sFilename);

        Texture texture;

    };

}


#endif //SCRATCH3D_MESH_H
