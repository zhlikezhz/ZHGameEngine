#include "Mesh.hpp"
#include "Material.hpp"
#include "GLShader.hpp"
#include "GLRender.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "SceneManager.hpp"
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
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    m_strPath = path.substr(0, path.find_last_of('/'));

    Camera* camera = SceneManager::getInstance()->getMainScene()->getMainCamera();
    camera->setY(7);
    camera->setZ(20);


    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for(int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Model* Model::processMesh(aiMesh* aimesh, const aiScene* aiscene)
{
    GameObject* model = new GameObject();
    model->addComponent<Transform>();
    Mesh* mesh = model->addComponent<Mesh>();
    Material* material = model->addComponent<Material>();
    GLShader* shader = GLShader::createFromFile("/Users/zouhao/Code/github/res/shader/default_vertex.gl", "/Users/zouhao/Code/github/res/shader/default_fragment.gl");
    material->setShader(shader);
    model->addComponent<GLRender>();

    bool hasUV = false;
    if (aimesh->mTextureCoords[0]) {
        hasUV = true;
    }

    for (int i = 0; i < aimesh->mNumVertices; i++) {
        mesh->addPoint(glm::vec3(aimesh->mVertices[i].x, 
                    aimesh->mVertices[i].y,
                    aimesh->mVertices[i].z));

        // mesh->addNormal(glm::vec3(aimesh->mNormals[i].x,
        //             aimesh->mNormals[i].y,
        //             aimesh->mNormals[i].z));

        if (hasUV) {
            mesh->addUV(glm::vec2(aimesh->mTextureCoords[0][i].x, 
                        aimesh->mTextureCoords[0][i].y));
        }
    }

    for(int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace face = aimesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++) {
            mesh->addIndex(face.mIndices[j]);
        }
    }

    if (aimesh->mMaterialIndex >= 0) {
        aiMaterial* aimaterial = aiscene->mMaterials[aimesh->mMaterialIndex];

        char buff[1024];
        for (int i = 0; i < aimaterial->GetTextureCount(aiTextureType_DIFFUSE); i++) {
            aiString textureName;
            aimaterial->GetTexture(aiTextureType_DIFFUSE, i, &textureName);
            sprintf(buff, "%s/%s", m_strPath.c_str(), textureName.C_Str());

            ShaderParameterValue value;
            value.texture = Texture::createFromFile(buff);
            material->addValue("texture_diffuse0", ShaderParameterType::TEXTURE, value);
        }

        for (int i = 0; i < aimaterial->GetTextureCount(aiTextureType_SPECULAR); i++) {
            aiString textureName;
            aimaterial->GetTexture(aiTextureType_SPECULAR, i, &textureName);
            sprintf(buff, "%s/%s", m_strPath.c_str(), textureName.C_Str());

            ShaderParameterValue value;
            value.texture = Texture::createFromFile(buff);
            material->addValue("texture_specular0", ShaderParameterType::TEXTURE, value);
        }
    }

    // return model;
    return NULL;
}

Model* Model::createModel(std::string path)
{
    Model* model = new Model(path);
    return model;
}

void Model::update()
{
    GameObject::update();

    // if (transform != NULL) {
    //     float off = 1.0f;
    //     float y = transform->getRotateY();
    //     if (y + off >= 360.0f) {
    //         transform->setRotateY(0.0f);
    //     } else {
    //         transform->setRotateY(y + off);
    //     }
    // }
}