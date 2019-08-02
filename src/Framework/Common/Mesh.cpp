#include "Mesh.hpp"
using namespace ZH;

Mesh::Mesh()
:m_vUV(),
m_vPoints(),
m_bDirty(true)
{

}

Mesh::~Mesh()
{

}

void Mesh::addPoint(float x, float y, float z)
{
    Point point(x, y, z);
    addPoint(point);
}

void Mesh::addPoint(Point point)
{
    m_vPoints.push_back(point);
    m_bDirty = true;
}

void Mesh::addPoints(std::vector<Point>& points)
{
    m_vPoints.insert(m_vPoints.end(), points.begin(), points.end());
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

float* Mesh::getPoints() 
{
    int num = m_vPoints.size();
    float* points = nullptr;
    if (num > 0) {
        points = new float[num * 3];
        std::vector<Point>::const_iterator iter = m_vPoints.cbegin();
        for (int i = 0; i < num; i++) {
            std::vector<Point>::const_iterator tr = iter + i;

            int off = i * 3;
            points[off] = tr->x;
            points[off+1] = tr->y;
            points[off+2] = tr->z;
        }
    }
    return points;
}
    
