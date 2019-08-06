#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "GameObject.hpp"

namespace ZH
{
    class Camera : public GameObject
    {
        public:
            Camera();
            ~Camera();

            inline float getFOV() {return m_fFOV;}
            inline float getFarPanel() {return m_fFarPanel;}
            inline float getNearPanel() {return m_fNearPanel;}
            inline void setFOV(float fov) { m_fFOV = fov;}
            inline void setFarPanel(float far) {m_fFarPanel = far;}
            inline void setNearPanel(float near) {m_fNearPanel = near;}

            inline glm::vec3 getPosition() {return m_vec3Position;}
            inline float getX() { return m_vec3Position.x;}
            inline float getY() { return m_vec3Position.y;}
            inline float getZ() { return m_vec3Position.z;}

            void setX(float);
            void setY(float);
            void setZ(float);
            void setPosition(float, float, float);
            void setPosition(glm::vec3);

            inline glm::vec3 getRotate() {return m_vec3Rotate;}
            inline float getRotateX() {return m_vec3Rotate.x;}
            inline float getRotateY() {return m_vec3Rotate.y;}
            inline float getRotateZ() {return m_vec3Rotate.z;}

            void setRotateX(float);
            void setRotateY(float);
            void setRotateZ(float);
            void setRotate(float, float, float);
            void setRotate(glm::vec3);

            void recalViewMatrix();
            glm::mat4 getViewMatrix();

            inline bool isDirty() { return m_bIsDirty;}
            inline void setDirty(bool dirty) { m_bIsDirty = dirty; }

        private:
            bool m_bIsDirty;

            float m_fFOV;
            float m_fFarPanel;
            float m_fNearPanel;

            glm::vec3 m_vec3Rotate;
            glm::vec3 m_vec3Position;
            glm::mat4 m_mat4View;
    };
}