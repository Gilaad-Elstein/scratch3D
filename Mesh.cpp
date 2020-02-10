//
// Created by gilaad on 1/24/20.
//

#include <sstream>
#include <fstream>
#include <utility>
#include "Mesh.h"
#include "structs/Vec3.h"
#include "structs/Matrix4x4.h"

namespace Scratch3d {

    void rotateVertexList(float x, float y, float z, std::vector<Vec3> &vertices) {
        Matrix4x4 mRotation = Matrix4x4::MakeXRotationMatrix(x) *
                              Matrix4x4::MakeYRotationMatrix(y) *
                              Matrix4x4::MakeZRotationMatrix(z);
        for (auto &vertex : vertices) {
            vertex *= mRotation;
        }
    }


    Mesh Mesh::GetMeshFromObjectFile(std::string const &sFilename) {
        Mesh m{};
        std::ifstream f(sFilename);
        if (!f.is_open()) {
            throw std::runtime_error("Error: Failed to open " + sFilename);
        }
        float maxAbsVal = 0;

    std::vector<Vec2> textureVerts;
        while (!f.eof()) {
            std::string line;
            std::getline(f, line);
            if (line[0] == 'v') {
                if (line[1] == 'n') { continue; }

                std::stringstream ss(line);
                char skipChar = 0;

                if (line[1] == 't') {
                ss >> skipChar >> skipChar >> skipChar;
                float d1; ss >> d1;
                ss >> skipChar;
                float d2; ss >> d2;
                ss >> skipChar;
                textureVerts.emplace_back(Vec2{d1, d2});
                } else if (line[1] == ' ') {
                    ss >> skipChar;
                    float px = 0;
                    ss >> px;
                    if (px > maxAbsVal) { maxAbsVal = px; }
                    float py = 0;
                    ss >> py;
                    if (py > maxAbsVal) { maxAbsVal = py; }
                    float pz = 0;
                    ss >> pz;
                    if (pz > maxAbsVal) { maxAbsVal = pz; }
                    m.rawVertices.emplace_back(Vec3{px, py, pz});
                }
            }
            if (line[0] == 'f') {
                Face face;
                std::stringstream ss(line);
                char skipChar = 0;
                int val = 0;
                ss >> skipChar;
                if (ss.str().find_first_of('/', 0) != std::string::npos) {
                    std::vector<size_t> indices;
                    std::vector<Vec2> texIndices;
                    int valCount = 0;
                    while (ss >> val) {
                        valCount++;
                        switch ((valCount - 1) % 3) {
                            case 0:
                                indices.emplace_back(val - 1); //obj indices are 1 based.
                                ss >> skipChar;
                                break;
                            case 1:
                            texIndices.emplace_back(textureVerts[val - 1]); //obj indices are 1 based.
                                ss >> skipChar;
                                break;
                            case 2:
                            default:
                                break;
                        }
                    }
                    face = Face{indices[0], indices[1], indices[2], texIndices};
                }
//                else {
//                    while (ss >> val) {
//                        faceIndexList.iVertices.emplace_back(val - 1); //obj indices are 1 based.
//                    }
//                }
                m.facesIndexLists.emplace_back(face);
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

    Mesh Mesh::GetTestCube(const float side) {
        Mesh m{};

        m.rawVertices.emplace_back(-side, -side, -side); // 0
        m.rawVertices.emplace_back(side, -side, -side); // 1
        m.rawVertices.emplace_back(-side, side, -side); // 2
        m.rawVertices.emplace_back(side, side, -side); // 3
        m.rawVertices.emplace_back(-side, -side, side); // 4
        m.rawVertices.emplace_back(side, -side, side); // 5
        m.rawVertices.emplace_back(-side, side, side); // 6
        m.rawVertices.emplace_back(side, side, side); // 7

        m.facesIndexLists.emplace_back(Face{0, 2, 1, std::vector<Vec2>{Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{2, 3, 1, std::vector<Vec2>{Vec2{0, 1}, Vec2{1, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{1, 3, 5, std::vector<Vec2>{Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{3, 7, 5, std::vector<Vec2>{Vec2{0, 1}, Vec2{1, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{2, 6, 3, std::vector<Vec2>{Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{3, 6, 7, std::vector<Vec2>{Vec2{1, 0}, Vec2{0, 1}, Vec2{1, 1}}});
        m.facesIndexLists.emplace_back(Face{4, 5, 7, std::vector<Vec2>{Vec2{0, 1}, Vec2{0, 0}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{4, 7, 6, std::vector<Vec2>{Vec2{0, 1}, Vec2{1, 0}, Vec2{1, 1}}});
        m.facesIndexLists.emplace_back(Face{0, 4, 2, std::vector<Vec2>{Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{2, 4, 6, std::vector<Vec2>{Vec2{1, 0}, Vec2{0, 1}, Vec2{1, 1}}});
        m.facesIndexLists.emplace_back(Face{0, 1, 4, std::vector<Vec2>{Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}});
        m.facesIndexLists.emplace_back(Face{1, 5, 4, std::vector<Vec2>{Vec2{0, 1}, Vec2{1, 1}, Vec2{1, 0}}});

        return m;
    }

    void Mesh::translate(float x, float y, float z) {
        for (auto &vertex : manipulatedVertices) {
            vertex.x += x;
            vertex.y += y;
            vertex.z += z;
        }
    }

    void Mesh::transform(int w, int h) {
        for (auto &vertex : manipulatedVertices) {
            float inverseZ = 1.0f / vertex.z;
            vertex.x = (vertex.x * inverseZ + 1) * static_cast<float>(w) / 2;
            vertex.y = (vertex.y * w/(float)h * inverseZ + 1) * static_cast<float>(h) / 2;
        }
    }

    void Mesh::transformNoPerspective(int w, int h) {
        for (auto &vertex : manipulatedVertices) {
            vertex.x = (vertex.x + 1) * static_cast<float>(w) / 2;
            vertex.y = (vertex.y + 1) * static_cast<float>(h) / 2;
        }
    }

    Face::Face(size_t v1, size_t v2, size_t v3) {
        iVertices.emplace_back(v1);
        iVertices.emplace_back(v2);
        iVertices.emplace_back(v3);
    }

    Face::Face(size_t v1, size_t v2, size_t v3, std::vector<Vec2> texCoords_) : Face(v1, v2, v3) {
        texCoords = std::move(texCoords_);
    }

    void Mesh::resetTransformations() {
        manipulatedVertices.clear();
        visibleFaces.clear();
        for (const auto &vertex : rawVertices) {
            manipulatedVertices.emplace_back(vertex);
        }
    }

    std::vector<TransformedFace> Mesh::getTransformedFaces() {
        std::vector<TransformedFace> faces;
        int i = -1;
        for (auto &faceIndexList : facesIndexLists) {
            i++;
            TransformedFace face;
            if (!visibleFaces.empty() && !visibleFaces[i]) continue;
            for (const auto &vertexIndex : facesIndexLists[i].iVertices) {
                face.vertices.emplace_back(manipulatedVertices[vertexIndex]);
            }
            for (const auto &texCoord : facesIndexLists[i].texCoords) {
                face.texCoords.emplace_back(texCoord);
            }
            faces.emplace_back(face);
        }
        return faces;
    }

    void Mesh::cullBackFaces() {
        for (auto &faceIndexList : facesIndexLists) {
            Vec3 line1 =
                    manipulatedVertices[faceIndexList.iVertices[1]] - manipulatedVertices[faceIndexList.iVertices[0]];
            Vec3 line2 =
                    manipulatedVertices[faceIndexList.iVertices[2]] - manipulatedVertices[faceIndexList.iVertices[0]];
            Vec3 normal = line1.CrossProduct(line2);
            bool isVisible = normal.DotProduct(manipulatedVertices[faceIndexList.iVertices[0]]) <= 0;
            visibleFaces.emplace_back(isVisible);
        }
    }

    void Mesh::rotateRaw(float x, float y, float z) {
        rotateVertexList(x, y, z, rawVertices);
    }

    void Mesh::rotate(float x, float y, float z) {
        rotateVertexList(x, y, z, manipulatedVertices);
    }

    void Mesh::invertRawXY() {
        for(auto& vertex : rawVertices){
            vertex.x *= -1;
            vertex.y *= -1;
        }
    }

}