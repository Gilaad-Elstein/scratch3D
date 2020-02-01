//
// Created by gilaad on 1/24/20.
//

#include <sstream>
#include <fstream>
#include "MeshObject.h"
#include "Vec3d.h"
#include "Matrix4x4.h"


MeshObject MeshObject::GetMeshFromObjectFile(std::string const &sFilename) {
    MeshObject m{};
    std::ifstream f(sFilename);
    if (!f.is_open()) {
        throw std::runtime_error("Error: Failed to open " + sFilename);
    }
    float maxAbsVal = 0;

//    std::vector<Vec3d> textureVerts;
    while (!f.eof()) {
        std::string line;
        std::getline(f, line);
        if (line[0] == 'v') {
            if (line[1] == 'n') { continue; }

            std::stringstream ss(line);
            char skipChar;

            if (line[1] == 't') {
                continue;
//                ss >> skipChar >> skipChar >> skipChar;
//                float d1; ss >> d1;
//                ss >> skipChar;
//                float d2; ss >> d2;
//                ss >> skipChar;
//                textureVerts.emplace_back(Vec3d{d1, d2});
            } else if (line[1] == ' ') {
                ss >> skipChar;
                float px;
                ss >> px;
                if (px > maxAbsVal) { maxAbsVal = px; }
                float py;
                ss >> py;
                if (py > maxAbsVal) { maxAbsVal = py; }
                float pz;
                ss >> pz;
                if (pz > maxAbsVal) { maxAbsVal = pz; }
                m.rawVertices.emplace_back(Vec3d{px, py, pz});
            }
        }
        if (line[0] == 'f') {
            std::stringstream ss(line);
            char skipChar;
            int val;
            FaceIndexList faceIndexList;
            ss >> skipChar;
            if (ss.str().find_first_of('/', 0) != std::string::npos) {
                int valCount = 0;
                while (ss >> val) {
                    valCount++;
                    switch ((valCount - 1) % 3) {
                        case 0:
                            faceIndexList.iVertices.emplace_back(val - 1); //obj indices are 1 based.
                            ss >> skipChar;
                            break;
                        case 1:
//                            p.textureCoords.emplace_back(textureVerts[val - 1]); //obj indices are 1 based.
                            ss >> skipChar;
                            break;
                        case 2:
                        default:
                            break;
                    }
                }
            } else {
                while (ss >> val) {
                    faceIndexList.iVertices.emplace_back(val - 1); //obj indices are 1 based.
                }
            }
            m.facesIndexLists.emplace_back(faceIndexList);
        }
    }
    if (maxAbsVal > 1) {
        for (auto &vertex : m.rawVertices) {
            vertex.x /= maxAbsVal;
            vertex.y /= maxAbsVal;
            vertex.z /= maxAbsVal;
        }
    }
    return m;
}

MeshObject MeshObject::GetTestCube(const float side) {
    MeshObject m{};

    m.rawVertices.emplace_back(-side, -side, -side ); // 0
    m.rawVertices.emplace_back(side, -side, -side ); // 1
    m.rawVertices.emplace_back(-side, side, -side ); // 2
    m.rawVertices.emplace_back(side, side, -side ); // 3
    m.rawVertices.emplace_back(-side, -side, side ); // 4
    m.rawVertices.emplace_back(side, -side, side ); // 5
    m.rawVertices.emplace_back(-side, side, side ); // 6
    m.rawVertices.emplace_back(side, side, side ); // 7

    m.facesIndexLists.emplace_back(FaceIndexList{0, 2, 1});
    m.facesIndexLists.emplace_back(FaceIndexList{2, 3, 1});
    m.facesIndexLists.emplace_back(FaceIndexList{1, 3, 5});
    m.facesIndexLists.emplace_back(FaceIndexList{3, 7, 5});
    m.facesIndexLists.emplace_back(FaceIndexList{2, 6, 3});
    m.facesIndexLists.emplace_back(FaceIndexList{3, 6, 7});
    m.facesIndexLists.emplace_back(FaceIndexList{4, 5, 7});
    m.facesIndexLists.emplace_back(FaceIndexList{4, 7, 6});
    m.facesIndexLists.emplace_back(FaceIndexList{0, 4, 2});
    m.facesIndexLists.emplace_back(FaceIndexList{2, 4, 6});
    m.facesIndexLists.emplace_back(FaceIndexList{0, 1, 4});
    m.facesIndexLists.emplace_back(FaceIndexList{1, 5, 4});

    return m;
}

void MeshObject::translate(float x, float y, float z){
    for(auto& vertex : manipulatedVertices){
        vertex.x += x;
        vertex.y += y;
        vertex.z += z;
    }
}

void MeshObject::transform(int w, int h){
    for(auto &vertex : manipulatedVertices){
        const float inverseZ = 1.0f / vertex.z;
        vertex.x = (vertex.x * inverseZ + 1) * static_cast<float>(w) / 2;
        vertex.y = (vertex.y * inverseZ + 1) * static_cast<float>(h) / 2;
    }
}

void MeshObject::rotate(float x, float y, float z) {
    Matrix4x4 mRotation = Matrix4x4::MakeXRotationMatrix(x) *
                          Matrix4x4::MakeYRotationMatrix(y) *
                          Matrix4x4::MakeZRotationMatrix(z);
    for(auto& vertex : manipulatedVertices){
        vertex *= mRotation;
    }
}

FaceIndexList::FaceIndexList(size_t v1, size_t v2, size_t v3) {
    iVertices.emplace_back(v1);
    iVertices.emplace_back(v2);
    iVertices.emplace_back(v3);
}

void MeshObject::resetTransformations() {
    manipulatedVertices.clear();
    for(const auto& vertex : rawVertices){
        manipulatedVertices.emplace_back(vertex);
    }
}

std::vector<TransformedFace> MeshObject::getTransformedFaces() {
    std::vector<TransformedFace> faces;
    for(const auto& faceIndexList : facesIndexLists){
        TransformedFace face;
        for(const auto& vertexIndex : faceIndexList.iVertices){
            face.vertices.emplace_back(manipulatedVertices[vertexIndex]);
        }
        faces.emplace_back(face);
    }
    return faces;
}
