#pragma once
#include "Shader.hpp"
#include "glm/mat4x4.hpp"

namespace ZH
{
    class GLShader : public Shader
    {
        public:
            GLShader();
            ~GLShader();

            static GLShader* createFromFile(const char* , const char* );
            static GLShader* createFromMemory(const char* , const char* );

            void use();
            void setBool(const char* name, bool val);
            void setInt(const char* name, int val);
            void setUInt(const char* name, unsigned int val);
            void setFloat(const char* name, float val);
            void set3Float(const char* name, float val1, float val2, float val3);
            void setMat4(const char* name, glm::mat4 matrix);

        private:
            unsigned int m_uShaderProgramID;

        private:

            bool build(const char* , const char* );
            bool loadFromFile(const char* , char** );
    };
}