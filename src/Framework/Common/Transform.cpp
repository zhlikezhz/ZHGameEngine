#include "Transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace ZH;

Transform::Transform()
: m_vec3Position(0.0f,0.0f,0.0f),
m_vec3Scale(1.0f,1.0f,1.0f),
m_vec3Rotate(0.0f,0.0f,0.0f),
m_vec3WorldPosition(0.0f,0.0f,0.0f),
m_mat4Model(1.0f),
m_bIsDirty(false),
m_pParent(nullptr)
{

}

Transform::~Transform()
{

}

void Transform::setX(float x)
{
    if (m_vec3Position.x != 0) {
        m_vec3Position.x = x;
        setDirty(true);
    }
}

void Transform::setY(float y)
{
    if (m_vec3Position.y != 0) {
        m_vec3Position.y = y;
        setDirty(true);
    }
}

void Transform::setZ(float z)
{
    if (m_vec3Position.z != 0) {
        m_vec3Position.z = z;
        setDirty(true);
    }
}

void Transform::setPosition(glm::vec3 vec)
{
    if (m_vec3Position != vec) {
        m_vec3Position = vec;
        setDirty(true);
    }
}

void Transform::setPosition(float x, float y, float z=0)
{
    glm::vec3 vec(x, y, z);
    setPosition(vec);
}

float Transform::getWorldPositionX()
{
    calModelMatrix();
    return m_vec3WorldPosition.x;
}

float Transform::getWorldPositionY()
{
    calModelMatrix();
    return m_vec3WorldPosition.y;
}

float Transform::getWorldPositionZ()
{
    calModelMatrix();
    return m_vec3WorldPosition.z;
}

glm::vec3 Transform::getWorldPosition()
{
    calModelMatrix();
    return m_vec3WorldPosition;
}

void Transform::setScaleX(float x)
{
    if (m_vec3Scale.x != x) {
        m_vec3Scale.x = x;
        setDirty(true);
    }
}

void Transform::setScaleY(float y)
{
    if (m_vec3Scale.y != y) {
        m_vec3Scale.y = y;
        setDirty(true);
    }
}

void Transform::setScaleZ(float z)
{
    if (m_vec3Scale.z != z) {
        m_vec3Scale.z = z;
        setDirty(true);
    }
}

void Transform::setScale(glm::vec3 vec)
{
    if (m_vec3Scale != vec) {
        m_vec3Scale = vec;
        setDirty(true);
    }
}

void Transform::setScale(float x, float y, float z=0)
{
    setScale(glm::vec3(x, y, z));
}

void Transform::setRotateX(float x)
{
    if (m_vec3Rotate.x != x) {
        m_vec3Rotate.x = x;
        setDirty(true);
    }
}

void Transform::setRotateY(float y)
{
    if (m_vec3Rotate.y != y) {
        m_vec3Rotate.y = y;
        setDirty(true);
    }
}

void Transform::setRotateZ(float z)
{
    if (m_vec3Rotate.z != z) {
        m_vec3Rotate.z = z;
        setDirty(true);
    }
}

void Transform::setRotate(glm::vec3 vec)
{
    if (m_vec3Rotate != vec) {
        m_vec3Rotate = vec;
        setDirty(true);
    }
}

void Transform::setRotate(float x, float y, float z)
{
    setRotate(glm::vec3(x, y, z));
}

void Transform::setParent(Transform* parent)
{
    if (parent != nullptr && m_pParent != parent) {
        m_pParent = parent;
        setDirty(true);
    }
}

glm::mat4 Transform::getModelMatrix()
{
    calModelMatrix();
    return m_mat4Model;
}

// 先缩放、绕z轴旋转、绕x轴旋转、绕y轴旋转、最后平移
void Transform::calModelMatrix()
{
    if (isDirty() || (m_pParent != nullptr && m_pParent->isDirty())) {
        glm::mat4 trans = glm::mat4(1.0f);
        if (m_pParent != nullptr) {
            trans = m_pParent->getModelMatrix();
        }
        trans = glm::translate(trans, glm::vec3(getX(), getY(), getX()));
        trans = glm::rotate(trans, glm::radians(getRotateY()), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(getRotateX()), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(getRotateZ()), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(getScaleX(), getScaleY(), getScaleZ()));
        m_vec3WorldPosition = trans * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        m_mat4Model = trans;
        setDirty(false);
    }
}