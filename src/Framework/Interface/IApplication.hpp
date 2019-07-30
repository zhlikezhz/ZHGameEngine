#pragma once
#include "Interface.hpp"
#include "IRuntimeModule.hpp"
#include "GfxConfiguration.h"

namespace ZH
{
    class IApplication : public IRuntimeModule
    {
        public:
            virtual int Initialize() = 0;
            virtual void Finalize() = 0;
            virtual void Tick() = 0;
            virtual bool IsQuit() = 0;
            virtual GfxConfiguration& GetConfiguration() = 0;
    };
}