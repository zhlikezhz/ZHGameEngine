#pragma once
#include "Component.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace ZH
{
    class Transform : public Component
    {
        DECLARE_CLASS(Transform)

        public:
            Transform();
            ~Transform();

            // local position
            inline float getX() {return m_vec3Position.x;}
            inline float getY() {return m_vec3Position.y;}
            inline float getZ() {return m_vec3Position.z;}
            inline glm::vec3 getPosition() { return m_vec3Position; }

            void setX(float x);
            void setY(float y);
            void setZ(float z);
            void setPosition(glm::vec3);
            void setPosition(float, float, float);

            // rotate
            inline float getRotateX() {return m_vec3Rotate.x;}
            inline float getRotateY() {return m_vec3Rotate.y;}
            inline float getRotateZ() {return m_vec3Rotate.z;}
            inline glm::vec3 getRotate() { return m_vec3Rotate; }

            void setRotateX(float x);
            void setRotateY(float y);
            void setRotateZ(float z);
            void setRotate(glm::vec3);
            void setRotate(float, float, float);

            // scale
            inline float getScaleX() {return m_vec3Scale.x;}
            inline float getScaleY() {return m_vec3Scale.y;}
            inline float getScaleZ() {return m_vec3Scale.z;}
            inline glm::vec3 getScale() { return m_vec3Scale; }

            void setScaleX(float x);
            void setScaleY(float y);
            void setScaleZ(float z);
            void setScale(glm::vec3);
            void setScale(float, float, float);

            // // world position
            float getWorldPositionX();
            float getWorldPositionY(); 
            float getWorldPositionZ(); 
            glm::vec3 getWorldPosition();

            inline bool isDirty() { return m_bIsDirty; }
            inline void setDirty(bool dirty) { m_bIsDirty = dirty;}

            inline Transform* getParent() { return m_pParent; }
            inline void setParent(Transform* parent);

            glm::mat4 getModelMatrix();
        
        private:
            void calModelMatrix();

        private:
            glm::vec3 m_vec3Scale;
            glm::vec3 m_vec3Rotate;
            glm::vec3 m_vec3Position;
            glm::vec3 m_vec3WorldPosition;
            glm::mat4 m_mat4Model;

            bool m_bIsDirty;
            Transform* m_pParent;
    };
}