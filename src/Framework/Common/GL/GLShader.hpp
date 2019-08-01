#pragma once
#include "Shader.hpp"

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
            void setb(const char* name, bool val);
            void seti(const char* name, int val);
            void setui(const char* name, unsigned int val);
            void setf(const char* name, float val);
            void set3f(const char* name, float val1, float val2, float val3);

        private:
            unsigned int m_uShaderProgramID;

        private:

            bool build(const char* , const char* );
            bool loadFromFile(const char* , char** );
    };
}