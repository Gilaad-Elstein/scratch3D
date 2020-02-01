//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_MESHOBJECT_H
#define SCRATCH3D_MESHOBJECT_H


#include <vector>
#include <sstream>
#include "Vec3d.h"

struct FaceIndexList{
    FaceIndexList() = default;
    FaceIndexList(size_t v1, size_t v2, size_t v3);
    std::vector<size_t> iVertices;
};

struct TransformedFace{
    std::vector<Vec3d> vertices;
};

class MeshObject {
    std::vector<Vec3d> rawVertices;
    std::vector<Vec3d> manipulatedVertices;
    std::vector<FaceIndexList> facesIndexLists;

public:
    void resetTransformations();
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);
    void transform(int w, int h);
    std::vector<TransformedFace> getTransformedFaces();


    static MeshObject GetTestCube(float size);
    static MeshObject GetMeshFromObjectFile(const std::string &sFilename);
};


#endif //SCRATCH3D_MESHOBJECT_H
