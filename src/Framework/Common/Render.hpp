#pragma once
#include "Component.hpp"

namespace ZH
{
    class Render : public Component
    {
        public:
            virtual void render();
    };
}