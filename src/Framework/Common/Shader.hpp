#pragma once
#include "glm/mat4x4.hpp"

namespace ZH
{
    class Shader
    {
        public:
            virtual void use() = 0;
            virtual void setBool(const char* name, bool val) = 0;
            virtual void setInt(const char* name, int val) = 0;
            virtual void setUInt(const char* name, unsigned int val) = 0;
            virtual void setFloat(const char* name, float val) = 0;
            virtual void set3Float(const char* name, float val1, float val2, float val3) = 0;
            virtual void setMat4(const char* name, glm::mat4 matrix) = 0;
    };
}