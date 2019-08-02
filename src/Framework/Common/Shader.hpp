#pragma once

namespace ZH
{
    class Shader
    {
        public:
            virtual void use() = 0;
            virtual void setb(const char* name, bool val) = 0;
            virtual void seti(const char* name, int val) = 0;
            virtual void setui(const char* name, unsigned int val) = 0;
            virtual void setf(const char* name, float val) = 0;
            virtual void set3f(const char* name, float val1, float val2, float val3) = 0;
    };
}