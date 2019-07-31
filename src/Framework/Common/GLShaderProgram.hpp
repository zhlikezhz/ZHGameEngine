#pragma once

namespace ZH
{
    class GLShaderProgram
    {
        public:
            static GLShaderProgram* createFromFile(const char* , const char* );
            static GLShaderProgram* createFromMemory(const char* , const char* );

            void use();
            void setb(const char* name, bool val);
            void seti(const char* name, int val);
            void setui(const char* name, unsigned int val);
            void setf(const char* name, float val);
            void set3f(const char* name, float val1, float val2, float val3);

        private:
            unsigned int m_uShaderProgramID;

        private:
            GLShaderProgram();
            ~GLShaderProgram();

            bool build(const char* , const char* );
            bool loadFromFile(const char* , char* );
    };
}