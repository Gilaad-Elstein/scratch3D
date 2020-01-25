//
// Created by gilaad on 1/24/20.
//

#ifndef SCRATCH3D_OBJECTMESH_H
#define SCRATCH3D_OBJECTMESH_H


#include <vector>
#include <sstream>
#include "Polygon.h"

struct ObjectMesh {
    std::vector<Polygon> polygons;

    static ObjectMesh GetMeshFromObjectFile(const std::string &sFilename);

    static ObjectMesh GetTestCube(double size);
};


#endif //SCRATCH3D_OBJECTMESH_H
