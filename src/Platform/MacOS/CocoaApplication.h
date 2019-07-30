#include "BaseApplication.hpp"
#include <Cocoa/Cocoa.h>

namespace ZH
{
    class CocoaApplication : public BaseApplication
    {
        public:
            CocoaApplication(GfxConfiguration &config)
                : BaseApplication(config) { };
            
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();
        
        protected:
            NSWindow* m_pWindow;
    };
}
