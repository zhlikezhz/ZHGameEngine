#pragma once
#include "Core/ISingleton.hpp"

namespace UpPower
{
    template<class T>
    class IManager : public ISingleton<T>
    {
        public:
            virtual void DoInit() = 0;
            virtual void DoUpdate() = 0;
            virtual void DoDestroy() = 0;
    };
}