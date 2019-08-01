#include "GLRender.hpp"
#include "glad/glad.h"
#include "Material.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include <vector>
using namespace ZH;

GLRender::GLRender()
{
    m_pMesh = nullptr;
    m_pShader = nullptr;
    m_pMaterial = nullptr;
}

GLRender::~GLRender()
{

}

void GLRender::render()
{
    if (m_pShader != nullptr) {
        if (m_pMesh != nullptr) {
            unsigned int VAO;
            unsigned int uvVBO;
            unsigned int triangleVBO;

            float* uvs = m_pMesh->getUV();
            float* triangles = m_pMesh->getTriangles();
            int num = m_pMesh->getTriangleNumber();

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &triangleVBO);
            glGenBuffers(1, &uvVBO);
            if (triangles != nullptr) {

                glBindVertexArray(VAO);
                glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
                glBufferData(GL_ARRAY_BUFFER, num * sizeof(float) * 3, triangles, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                if (uvs != nullptr) {
                    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
                    glBufferData(GL_ARRAY_BUFFER, num * sizeof(float) * 3, uvs, GL_STATIC_DRAW);
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                    glEnableVertexAttribArray(1);

                    delete[] uvs;
                }
                delete[] triangles;
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
            glBindVertexArray(0);

            m_pShader->use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, num);

            glDeleteBuffers(1, &uvVBO);
            glDeleteBuffers(1, &triangleVBO);
            glDeleteVertexArrays(1, &VAO);
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