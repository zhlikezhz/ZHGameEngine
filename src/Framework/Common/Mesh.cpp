#include "Mesh.hpp"
using namespace ZH;

IMPLEMENT_CLASS(Mesh)

Mesh::Mesh()
:m_vUVs(),
m_vPoints(),
m_vNormals(),
m_bDirty(true)
{

}

Mesh::~Mesh()
{

}

void Mesh::addPoint(glm::vec3 point)
{
    setDirty(true);
    m_vPoints.push_back(point);
}

void Mesh::addPoints(std::vector<glm::vec3>& points)
{
    setDirty(true);
    std::vector<glm::vec3>::iterator iter = points.begin();
    for (; iter != points.end(); iter++) {
        m_vPoints.push_back(*iter);
    }
}

void Mesh::addUV(glm::vec2 uv)
{
    setDirty(true);
    m_vUVs.push_back(uv);
}

void Mesh::addUVs(std::vector<glm::vec2>& uvs)
{
    setDirty(true);
    std::vector<glm::vec2>::iterator iter = uvs.begin();
    for (; iter != uvs.end(); iter++) {
        m_vUVs.push_back(*iter);
    }
}

void Mesh::addNormal(glm::vec3 normal)
{
    setDirty(true);
    m_vNormals.push_back(normal);
}

void Mesh::addNormals(std::vector<glm::vec3>& normals)
{
    setDirty(true);
    std::vector<glm::vec3>::iterator iter = normals.begin();
    for (; iter != normals.end(); iter++) {
        m_vNormals.push_back(*iter);
    }
}