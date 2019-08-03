#pragma once
#include "Transform.hpp"

namespace ZH
{
    class GameObject
    {
        public:
            GameObject();
            ~GameObject();

        public:
            Transform transform;
    };
}