#pragma once
#include <stdint.h>
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
            inline void setFOV(float fov) {m_fFOV = fov;}
            inline void setFarPanel(float farPanel) {m_fFarPanel = farPanel;}
            inline void setNearPanel(float nearPanel) {m_fNearPanel = nearPanel;}

        private:
            float m_fFOV;
            float m_fFarPanel;
            float m_fNearPanel;
    };
}