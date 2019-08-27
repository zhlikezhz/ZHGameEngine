#pragma once
#include "ISingleton.hpp"

namespace ZH
{
    template<class T>
    class IManager : public ISingleton<T>
    {
        public:
            virtual void init() = 0;
            virtual void destroy() = 0;
            virtual void update() = 0;
    };
}