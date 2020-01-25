//
// Created by gilaad on 1/24/20.
//

#include <sstream>
#include <fstream>
#include "ObjectMesh.h"
#include "Vec3d.h"


ObjectMesh ObjectMesh::GetMeshFromObjectFile(std::string const &sFilename)
{
    ObjectMesh m{};
    std::ifstream f(sFilename);
    if (!f.is_open()){
        throw std::runtime_error("Error: Failed to open " + sFilename);
    }
    double maxAbsVal = 0;

    std::vector<Vec3d> verts;
    std::vector<Vec3d> textureVerts;
    while (!f.eof())
    {
        std::string line;
        std::getline(f, line);
        if (line[0] == 'v')
        {
            if (line[1] == 'n') {continue;}

            std::stringstream ss(line);
            char skipChar;

            if (line[1] == 't') {
                ss >> skipChar >> skipChar >> skipChar;
                double d1; ss >> d1;
                ss >> skipChar;
                double d2; ss >> d2;
                ss >> skipChar;
                textureVerts.emplace_back(Vec3d{d1, d2});
            }

            else if (line[1] == ' '){
                ss >> skipChar;
                double px; ss >> px; if(px > maxAbsVal) { maxAbsVal = px;}
                double py; ss >> py; if(py > maxAbsVal) { maxAbsVal = py;}
                double pz; ss >> pz; if(pz > maxAbsVal) { maxAbsVal = pz;}
                verts.emplace_back(Vec3d{px, py, pz});
            }
        }
        if (line[0] == 'f')
        {
            std::stringstream ss(line);
            char skipChar;
            int val;
            ss >> skipChar;
            Polygon p;
            if(ss.str().find_first_of('/', 0) != std::string::npos){
                int valCount = 0;
                while (ss >> val){
                    valCount++;
                    switch ((valCount-1)%3){
                        case 0:
                            p.points.emplace_back(verts[val - 1]); //obj indices are 1 based.
                            ss >> skipChar;
                            break;
                        case 1:
                            p.textureCoords.emplace_back(textureVerts[val - 1]); //obj indices are 1 based.
                            ss >> skipChar;
                            break;
                        case 2:
                        default:
                            break;
                    }
                }
            }
            else{
                while (ss >> val){
                    p.points.emplace_back(verts[val - 1]); //obj indices are 1 based.
                }
            }
            m.polygons.emplace_back(p);
        }
    }
    if (maxAbsVal > 1){
        for(auto& poly : m.polygons){
            for(auto& point: poly.points){
                point.x /= maxAbsVal;
                point.y /= maxAbsVal;
                point.z /= maxAbsVal;
            }
        }
    }
    return m;
}

ObjectMesh ObjectMesh::GetTestCube(double size) {
    ObjectMesh cube;
    Polygon p{};

    // SOUTH
    p.points.emplace_back(Vec3d{-size/100, -size/100, -size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{-size/100, -size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, -size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    // EAST
    p.points.emplace_back(Vec3d{size/100, -size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{size/100, -size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{size/100, -size/100, size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    // NORTH
    p.points.emplace_back(Vec3d{size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, -size/100, size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    // WEST
    p.points.emplace_back(Vec3d{-size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{-size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{-size/100, -size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    // TOP
    p.points.emplace_back(Vec3d{-size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{-size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{-size/100, size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, size/100});
    p.points.emplace_back(Vec3d{size/100, size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    // BOTTOM
    p.points.emplace_back(Vec3d{size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, -size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};
    p.points.emplace_back(Vec3d{size/100, -size/100, size/100});
    p.points.emplace_back(Vec3d{-size/100, -size/100, -size/100});
    p.points.emplace_back(Vec3d{size/100, -size/100, -size/100});
    cube.polygons.emplace_back(p);
    p = Polygon{};

    return cube;
}