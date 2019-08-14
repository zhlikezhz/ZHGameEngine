#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "glad/glad.h"
#include "Material.hpp"
#include "Mesh.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
using namespace ZH;
IMPLEMENT_CLASS(GLRender)

GLRender::GLRender()
{
    m_uiVAO = 0;
    m_uiUVVBO = 0;
    m_uiPointVBO = 0;
    m_uiNormalVBO = 0;
}

GLRender::~GLRender()
{

}

void GLRender::preproccessing()
{
    Mesh* mesh = (Mesh*)m_pObject->getComponent("Mesh");
    Material* material = (Material*)m_pObject->getComponent("Material");
    GLShader* shader = (GLShader*)material->getShader();
    Camera* camera = m_pObject->getCamera();
    Transform* transform = (Transform*)m_pObject->getComponent("Transform");

    if (mesh != nullptr && mesh->isDirty()) {
        if (m_uiVAO != 0) {
            glDeleteVertexArrays(1, &m_uiVAO);
        }
        if (m_uiUVVBO != 0) {
            glDeleteBuffers(1, &m_uiUVVBO);
        }
        if (m_uiPointVBO != 0) {
            glDeleteBuffers(1, &m_uiPointVBO);
        }
        if (m_uiNormalVBO != 0) {
            glDeleteBuffers(1, &m_uiNormalVBO);
        }

        std::vector<glm::vec3> points = mesh->getPoints();
        std::vector<glm::vec3> normals = mesh->getNormals();
        std::vector<glm::vec2> uvs = mesh->getUV();

        glGenVertexArrays(1, &m_uiVAO);
        glGenBuffers(1, &m_uiPointVBO);
        glGenBuffers(1, &m_uiUVVBO);

        if (points.size() > 0) {
            glBindVertexArray(m_uiVAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_uiPointVBO);
            glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            glEnableVertexAttribArray(0);
        }

        if (uvs.size() > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, m_uiUVVBO);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
            glEnableVertexAttribArray(1);
        }

        if (normals.size() > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, m_uiNormalVBO);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            glEnableVertexAttribArray(2);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        mesh->setDirty(false);
    }

    if (shader != nullptr && material != nullptr && material->isDirty()) {
        for (ShaderParameter2ID::const_iterator iter = m_mTextureIDs.cbegin(); iter != m_mTextureIDs.cend(); iter++) {
            glDeleteTextures(1, &iter->second);
        }
        m_mTextureIDs.clear();

        int count = 0;
        shader->use();
        const ShaderParameterList shaderParameters = material->getShaderParameters();
        for (ShaderParameterList::const_iterator iter = shaderParameters.cbegin(); iter != shaderParameters.cend(); iter++) {
            if (iter->type == ShaderParameterType::TEXTURE) {
                unsigned int textureID = 0;
                glGenTextures(1, &textureID);
                glBindTexture(GL_TEXTURE_2D, textureID);

                // 为当前绑定的纹理对象设置环绕、过滤方式
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                Texture* texture = iter->value.texture;
                int width = texture->getWidth();
                int height = texture->getHeight();
                const unsigned char* data = texture->getTextureData();
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                m_mTextureIDs.insert(ShaderParameter2ID::value_type(iter->name, textureID));
                shader->setInt(iter->name, count++);
            }
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        material->setDirty(false);
    }

    if (material != nullptr && camera != nullptr && camera->isDirty()) {
        ShaderParameterValue viewParameter;
        viewParameter.mat4x4 = camera->getViewMatrix();
        material->addValue("view", ShaderParameterType::MATRIX4, viewParameter);

        ShaderParameterValue modelParameter;
        modelParameter.mat4x4 = transform->getModelMatrix();
        material->addValue("model", ShaderParameterType::MATRIX4, modelParameter);

        ShaderParameterValue projectionParameter;
        projectionParameter.mat4x4 = glm::perspective(glm::radians(camera->getFOV()), 1.0f, camera->getFarPanel(), camera->getNearPanel());
        material->addValue("projection", ShaderParameterType::MATRIX4, projectionParameter);

        camera->setDirty(false);
    }
}

void GLRender::render()
{
    Mesh* mesh = (Mesh*)m_pObject->getComponent("Mesh");
    Material* material = (Material*)m_pObject->getComponent("Material");
    GLShader* shader = (GLShader*)material->getShader();
    if (shader != nullptr) {
        if (mesh != nullptr) {
            glEnable(GL_DEPTH_TEST);
            preproccessing();

            if (material != nullptr) {
                int count = 0;
                const ShaderParameterList shaderParameters = material->getShaderParameters();
                for (ShaderParameterList::const_iterator iter = shaderParameters.cbegin(); iter != shaderParameters.cend(); iter++) {
                    if (iter->type == ShaderParameterType::TEXTURE) {
                        if (count == 0) {
                            glActiveTexture(GL_TEXTURE0);
                        } else if (count == 1) {
                            glActiveTexture(GL_TEXTURE1);
                        } else if (count == 2) {
                            glActiveTexture(GL_TEXTURE2);
                        } else if (count == 3) {
                            glActiveTexture(GL_TEXTURE3);
                        } else if (count == 4) {
                            glActiveTexture(GL_TEXTURE4);
                        }
                        glBindTexture(GL_TEXTURE_2D, m_mTextureIDs[iter->name]);
                        count++;
                    }
                }
            }

            shader->use();
            if (material != nullptr) {
                const ShaderParameterList shaderParameters = material->getShaderParameters();
                for (ShaderParameterList::const_iterator iter = shaderParameters.cbegin(); iter != shaderParameters.cend(); iter++) {
                    if (iter->type == ShaderParameterType::BOOL) {
                        shader->setBool(iter->name, iter->value.valb);
                    } else if (iter->type == ShaderParameterType::INT) {
                        shader->setInt(iter->name, iter->value.vali);
                    } else if (iter->type == ShaderParameterType::UINT) {
                        shader->setUInt(iter->name, iter->value.valui);
                    } else if (iter->type == ShaderParameterType::FLOAT) {
                        shader->setFloat(iter->name, iter->value.valf);
                    } else if (iter->type == ShaderParameterType::VECTOR3F) {
                        shader->set3Float(iter->name, iter->value.val3f[0], iter->value.val3f[1], iter->value.val3f[2]);
                    } else if (iter->type == ShaderParameterType::MATRIX4) {
                        shader->setMat4(iter->name, iter->value.mat4x4);
                    }
                }
            }
            glBindVertexArray(m_uiVAO);

            int num = mesh->getPointNumber();
            glDrawArrays(GL_TRIANGLES, 0, num);
        }
    }
}

void GLRender::update(float delay)
{
    render();
}