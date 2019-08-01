#include "Mesh.hpp"
using namespace ZH;

Mesh::Mesh()
:m_vUV(),
m_vTriangles(),
m_bDirty(true)
{

}

Mesh::~Mesh()
{

}

void Mesh::addTriangle(float x, float y, float z)
{
    Triangle triangle(x, y, z);
    addTriangle(triangle);
}

void Mesh::addTriangle(Triangle triangle)
{
    m_vTriangles.push_back(triangle);
    m_bDirty = true;
}

void Mesh::addTriangles(std::vector<Triangle>& triangles)
{
    m_vTriangles.insert(m_vTriangles.end(), triangles.begin(), triangles.end());
    m_bDirty = true;
}

void Mesh::addUV(float x, float y, float z)
{
    UV uv(x, y, z);
    addUV(uv);
}

void Mesh::addUV(UV uv)
{
    m_vUV.push_back(uv);
    m_bDirty = true;
}

void Mesh::addUVs(std::vector<UV>& uvs)
{
    m_vUV.insert(m_vUV.begin(), uvs.begin(), uvs.end());
    m_bDirty = true;
}

float* Mesh::getUV() 
{ 
    int num = m_vUV.size();
    float* uvs = nullptr;
    if (num > 0) {
        uvs = new float[num * 3];
        std::vector<UV>::const_iterator iter = m_vUV.cbegin();
        for (int i = 0; i < num; i++) {
            std::vector<UV>::const_iterator uv = iter + i;

            int off = i * 3;
            uvs[off] = uv->x;
            uvs[off+1] = uv->y;
            uvs[off+2] = uv->z;
        }
    }
    return uvs;
}

float* Mesh::getTriangles() 
{
    int num = m_vTriangles.size();
    float* triangles = nullptr;
    if (num > 0) {
        triangles = new float[num * 3];
        std::vector<Triangle>::const_iterator iter = m_vTriangles.cbegin();
        for (int i = 0; i < num; i++) {
            std::vector<Triangle>::const_iterator tr = iter + i;

            int off = i * 3;
            triangles[off] = tr->x;
            triangles[off+1] = tr->y;
            triangles[off+2] = tr->z;
        }
    }
    return triangles;
}
    
