#include "Mesh.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "Model.hpp"
using namespace ZH;

Model::Model()
{
    init();
}

Model::Model(std::string path)
{
    initWithFile(path);
}

Model::~Model()
{

}

void Model::init()
{
    transform = addComponent<Transform>();
}

void Model::initWithFile(std::string path)
{
    init();
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    m_strPath = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Model* model = processMesh(mesh, scene);
        model->transform->setParent(this->transform);
    }

    for(int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Model* Model::processMesh(aiMesh* aimesh, const aiScene* aiscene)
{
    Model* model = new Model();
    Mesh* mesh = model->addComponent<Mesh>();

    bool hasUV = false;
    if (aimesh->mTextureCoords[0]) {
        hasUV = true;
    }

    for (int i = 0; i < aimesh->mNumVertices; i++) {
        mesh->addPoint(glm::vec3(aimesh->mVertices[i].x, 
                    aimesh->mVertices[i].y,
                    aimesh->mVertices[i].z));

        // mesh->addNormal(aimesh->mNormals[i].x,
        //             aimesh->mNormals[i].y,
        //             aimesh->mNormals[i].z);

        // if (hasUV) {
        //     mesh->addUV(aimesh->mTextureCoords[0][i].x, 
        //                 aimesh->mTextureCoords[0][i].y);
        // }
    }

    // if (aimesh->mMaterialIndex >= 0) {
    //     Material* material = model->addComponent<Material>();
    //     aiMaterial* aimaterial = aiscene->mMaterials[aimesh->mMaterialIndex];

    //     for (int i = 0; i < aimaterial->GetTextureCount(aiTextureType_DIFFUSE); i++) {
    //         aiString textureName;
    //         aimaterial->GetTexture(aiTextureType_DIFFUSE, i, &textureName);
    //         std::string fullPath = sprintf("%s/%s", m_strPath.c_str(), textureName.C_Str());

    //         ShaderParameterValue value;
    //         value.texture = Texture::createFromFile(fullPath);
    //         material->addValue(sprintf("texture_diffues_%d", i), ShaderParameterType.TEXTURE, value);
    //     }

    //     for (int i = 0; i < aimaterial->GetTextureCount(aiTextureType_SPECULAR); i++) {
    //         aiString textureName;
    //         aimaterial->GetTexture(aiTextureType_SPECULAR, i, &textureName);
    //         std::string fullPath = sprintf("%s/%s", m_strPath.c_str(), textureName.C_Str());

    //         ShaderParameterValue value;
    //         value.texture = Texture::createFromFile(fullPath);
    //         material->addValue(sprintf("texture_specular_%d", i), ShaderParameterType.TEXTURE, value);
    //     }
    // }

    return model;
}

Model* Model::createModel(std::string path)
{
    Model* model = new Model(path);
    return model;
}