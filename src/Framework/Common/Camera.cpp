#include "Camera.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
using namespace ZH;

Camera::Camera()
:m_bIsDirty(true),
m_fFOV(45.0f),
m_fFarPanel(0.1f),
m_fNearPanel(100.0f),
m_vec3Rotate(0.0f, 0.0f, 0.0f),
m_vec3Position(0.0f, 0.0f, 0.0f),
m_mat4View(1.0f)
{

}

Camera::~Camera()
{

}

void Camera::setX(float x)
{
    if (m_vec3Position.x != x) {
        m_vec3Position.x = x;
        setDirty(true);
    }
}

void Camera::setY(float y)
{
    if (m_vec3Position.y != y) {
        m_vec3Position.y = y;
        setDirty(true);
    }
}

void Camera::setZ(float z)
{
    if (m_vec3Position.z != z) {
        m_vec3Position.z = z;
        setDirty(true);
    }
}

void Camera::setPosition(glm::vec3 vec)
{
    if (m_vec3Position != vec) {
        m_vec3Position = vec;
        setDirty(true);
    }
}

void Camera::setPosition(float x, float y, float z=0)
{
    setPosition(glm::vec3(x, y, z));
}

void Camera::setRotateX(float x)
{
    if (m_vec3Rotate.x != x) {
        m_vec3Rotate.x = x;
        setDirty(true);
    }
}

void Camera::setRotateY(float y)
{
    if (m_vec3Rotate.y != y) {
        m_vec3Rotate.y = y;
        setDirty(true);
    }
}

void Camera::setRotateZ(float z)
{
    if (m_vec3Rotate.z != z) {
        m_vec3Rotate.z = z;
        setDirty(true);
    }
}

void Camera::setRotate(float x, float y, float z=0)
{
    setRotate(glm::vec3(x, y, z));
}

void Camera::setRotate(glm::vec3 vec)
{
    if (m_vec3Rotate != vec) {
        m_vec3Rotate = vec;
        setDirty(true);
    }
}

glm::mat4 Camera::getViewMatrix()
{
    recalViewMatrix();
    return m_mat4View;
}

void Camera::recalViewMatrix()
{
    if (isDirty()) {
        glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(m_vec3Rotate.x), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(m_vec3Rotate.z), glm::vec3(0.0, 0.0, 1.0));
        zAxis = glm::normalize(glm::vec3(trans * glm::vec4(zAxis, 1.0f)));
        yAxis = glm::normalize(glm::vec3(trans * glm::vec4(yAxis, 1.0f)));
        xAxis = glm::normalize(glm::vec3(trans * glm::vec4(xAxis, 1.0f)));


        m_mat4View = glm::mat4(xAxis.x, yAxis.x, zAxis.x, 0.0f,
                                xAxis.y, yAxis.y, zAxis.y, 0.0f,
                                xAxis.z, yAxis.z, zAxis.z, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);
        m_mat4View = glm::translate(m_mat4View, -m_vec3Position);
        setDirty(false);
    }
}