#include "Core/AssimpData.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include <iostream>
#include <vector>
using namespace UpPower;

AssimpData::AssimpData()
:m_UVs(),
m_Points(),
m_Normals(),
m_uiIndices(),
m_bDirty(true)
{

}

AssimpData::~AssimpData()
{

}

AssimpData* AssimpData::CreateFromFile(const char* filename)
{
    /*
    默认情况下，所有3D数据都在右手坐标系中提供，例如OpenGL使用的坐标系。
    在此坐标系中，+X 指向右侧，+Y 指向上方，+Z 指向屏幕外朝向观察者。
    输出面绕组为逆时针方向
    */
    const aiScene* scene = aiImportFile(filename, aiProcess_Triangulate|aiProcess_SortByPType);
    if (nullptr == scene)
    {
        std::cout<<"load model failure: "<<filename<<std::endl;
        return nullptr;
    }

    AssimpData* mesh = new AssimpData();
    aiReleaseImport(scene);
    return mesh;
}

AssimpData* AssimpData::CreateFromMemory(const char* buffer, int length)
{
    /*
    默认情况下，所有3D数据都在右手坐标系中提供，例如OpenGL使用的坐标系。
    在此坐标系中，+X 指向右侧，+Y 指向上方，+Z 指向屏幕外朝向观察者。
    输出面绕组为逆时针方向
    */
    const aiScene* scene = aiImportFileFromMemory(buffer, length, aiProcess_Triangulate|aiProcess_SortByPType, nullptr);
    if (nullptr == scene)
    {
        std::cout<<"load model failure."<<std::endl;
        return nullptr;
    }

    AssimpData* mesh = new AssimpData();
    aiReleaseImport(scene);
    return mesh;
}

void AssimpData::InitFromScene(const aiScene* scene)
{
    m_UVs.resize(scene->mNumMeshes);
    m_Points.resize(scene->mNumMeshes);
    m_Normals.resize(scene->mNumMeshes);
    for (int i = 0 ; i < scene->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        InitMesh(mesh);
    }
}

void AssimpData::InitMesh(const aiMesh* mesh)
{
    
}

void AssimpData::AddPoint(glm::vec3 point)
{
    SetDirty(true);
    m_Points.push_back(point);
}

void AssimpData::AddPoints(std::vector<glm::vec3>& points)
{
    SetDirty(true);
    std::vector<glm::vec3>::iterator iter = points.begin();
    for (; iter != points.end(); iter++) 
	{
        m_Points.push_back(*iter);
    }
}

void AssimpData::AddUV(glm::vec2 uv)
{
    SetDirty(true);
    m_UVs.push_back(uv);
}

void AssimpData::AddUVs(std::vector<glm::vec2>& uvs)
{
    SetDirty(true);
    std::vector<glm::vec2>::iterator iter = uvs.begin();
    for (; iter != uvs.end(); iter++) 
	{
        m_UVs.push_back(*iter);
    }
}

void AssimpData::AddNormal(glm::vec3 normal)
{
    SetDirty(true);
    m_Normals.push_back(normal);
}

void AssimpData::AddNormals(std::vector<glm::vec3>& normals)
{
    SetDirty(true);
    std::vector<glm::vec3>::iterator iter = normals.begin();
    for (; iter != normals.end(); iter++) 
	{
        m_Normals.push_back(*iter);
    }
}

void AssimpData::AddIndex(unsigned int index)
{
    SetDirty(true);
    m_uiIndices.push_back(index);
}

void AssimpData::AddIndices(std::vector<unsigned int>& indices)
{
    SetDirty(true);
    std::vector<unsigned int>::iterator iter = indices.begin();
    for (; iter != indices.end(); iter++) 
	{
        m_uiIndices.push_back(*iter);
    }
}