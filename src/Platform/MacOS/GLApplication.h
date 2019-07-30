#include "BaseApplication.hpp"
#include <Cocoa/Cocoa.h>

namespace ZH
{
    class GLApplication : public BaseApplication
    {
        public:
          GLApplication(GfxConfiguration &config)
                : BaseApplication(config) { };
            
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();
        
        protected:
            NSWindow* m_pWindow;
    };
}
