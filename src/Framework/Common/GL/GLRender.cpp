#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "glad/glad.h"
#include "Material.hpp"
#include "Mesh.hpp"
#include <vector>
using namespace ZH;

GLRender::GLRender()
{
    m_uiVAO = 0;
    m_uiUVVBO = 0;
    m_uiPointVBO = 0;

    m_pMesh = nullptr;
    m_pShader = nullptr;
    m_pMaterial = nullptr;
}

GLRender::~GLRender()
{

}

void GLRender::preproccessing()
{
    if (m_pMesh != nullptr && m_pMesh->isDirty()) {
        if (m_uiVAO != 0) {
            glDeleteVertexArrays(1, &m_uiVAO);
        }
        if (m_uiUVVBO != 0) {
            glDeleteBuffers(1, &m_uiUVVBO);
        }
        if (m_uiPointVBO != 0) {
            glDeleteBuffers(1, &m_uiPointVBO);
        }

        float* uvs = m_pMesh->getUV();
        float* points = m_pMesh->getPoints();
        int num = m_pMesh->getPointNumber();
            
        glGenVertexArrays(1, &m_uiVAO);
        glGenBuffers(1, &m_uiPointVBO);
        glGenBuffers(1, &m_uiUVVBO);
        if (points != nullptr) {
            glBindVertexArray(m_uiVAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_uiPointVBO);
            glBufferData(GL_ARRAY_BUFFER, num * sizeof(float) * 3, points, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            if (uvs != nullptr) {
                glBindBuffer(GL_ARRAY_BUFFER, m_uiUVVBO);
                glBufferData(GL_ARRAY_BUFFER, num * sizeof(float) * 3, uvs, GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(1);

                delete[] uvs;
            }
            delete[] points;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        glBindVertexArray(0);
        m_pMesh->setDirty(false);
    }

    if (m_pShader != nullptr && m_pMaterial != nullptr && m_pMaterial->isDirty()) {
        for (ShaderParameter2ID::const_iterator iter = m_mTextureIDs.cbegin(); iter != m_mTextureIDs.cend(); iter++) {
            glDeleteTextures(1, &iter->second);
        }
        m_mTextureIDs.clear();

        int count = 0;
        m_pShader->use();
        const ShaderParameterList shaderParameters = m_pMaterial->getShaderParameters();
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
                m_pShader->setInt(iter->name, count++);
            }
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        m_pMaterial->setDirty(false);
    }
}

void GLRender::render()
{
    if (m_pShader != nullptr) {
        if (m_pMesh != nullptr) {
            glEnable(GL_DEPTH_TEST);
            preproccessing();

            if (m_pMaterial != nullptr) {
                int count = 0;
                const ShaderParameterList shaderParameters = m_pMaterial->getShaderParameters();
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

            m_pShader->use();
            if (m_pMaterial != nullptr) {
                const ShaderParameterList shaderParameters = m_pMaterial->getShaderParameters();
                for (ShaderParameterList::const_iterator iter = shaderParameters.cbegin(); iter != shaderParameters.cend(); iter++) {
                    if (iter->type == ShaderParameterType::BOOL) {
                        m_pShader->setBool(iter->name, iter->value.valb);
                    } else if (iter->type == ShaderParameterType::INT) {
                        m_pShader->setInt(iter->name, iter->value.vali);
                    } else if (iter->type == ShaderParameterType::UINT) {
                        m_pShader->setUInt(iter->name, iter->value.valui);
                    } else if (iter->type == ShaderParameterType::FLOAT) {
                        m_pShader->setFloat(iter->name, iter->value.valf);
                    } else if (iter->type == ShaderParameterType::VECTOR3F) {
                        m_pShader->set3Float(iter->name, iter->value.val3f[0], iter->value.val3f[1], iter->value.val3f[2]);
                    } else if (iter->type == ShaderParameterType::MATRIX4) {
                        m_pShader->setMat4(iter->name, iter->value.mat4x4);
                    }
                }
            }
            glBindVertexArray(m_uiVAO);

            int num = m_pMesh->getPointNumber();
            glDrawArrays(GL_TRIANGLES, 0, num);
        }
    }
}

void GLRender::setMesh(Mesh* mesh)
{
    m_pMesh = mesh;
}

void GLRender::setShader(Shader* shader)
{
    m_pShader = shader;
}

void GLRender::setMaterial(Material* mat)
{
    m_pMaterial = mat;
}
