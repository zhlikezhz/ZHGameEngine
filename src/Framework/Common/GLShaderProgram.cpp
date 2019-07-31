#include "GLShaderProgram.hpp"
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace ZH;

GLShaderProgram::GLShaderProgram()
:m_uShaderProgramID(0)
{

}

GLShaderProgram::~GLShaderProgram()
{
    if (m_uShaderProgramID > 0) {
        glDeleteProgram(m_uShaderProgramID);
    }
}

GLShaderProgram* GLShaderProgram::createFromFile(const char* vertexFile, const char* fragmentFile)
{
    GLShaderProgram* program = new GLShaderProgram();

    char* vBuff = nullptr;
    char* fBuff = nullptr;
    if (program->loadFromFile(vertexFile, vBuff) && program->loadFromFile(fragmentFile, fBuff)) {
        if (program->build(vBuff, fBuff)) {
            if (vBuff != nullptr) delete [] vBuff;
            if (fBuff != nullptr) delete [] fBuff;
            return program;
        }
    }
    if (vBuff != nullptr) delete [] vBuff;
    if (fBuff != nullptr) delete [] fBuff;
    delete program;
    return nullptr;
}

GLShaderProgram* GLShaderProgram::createFromMemory(const char* vBuff, const char* fBuff)
{
    GLShaderProgram* program = new GLShaderProgram();
    if (program->build(vBuff, fBuff)) {
        return program;
    }
    delete program;
    return nullptr;
}

bool GLShaderProgram::build(const char* vBuff, const char* fBuff)
{
    int status;
    char infoLog[512];

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vBuff, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glDeleteShader(vShader);
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fBuff, NULL);
    glCompileShader(fShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    m_uShaderProgramID = glCreateProgram();
    glAttachShader(m_uShaderProgramID, vShader);
    glAttachShader(m_uShaderProgramID, fShader);
    glLinkProgram(m_uShaderProgramID);

    glGetProgramiv(m_uShaderProgramID, GL_LINK_STATUS, &status);
    if(!status) {
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        glGetProgramInfoLog(m_uShaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return true;
}

bool GLShaderProgram::loadFromFile(const char* filePath, char* buffer)
{
    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(filePath);
        std::stringstream strStream;
        strStream << shaderFile.rdbuf();
        shaderFile.close();
        code = strStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    int num = strlen(code.c_str()) + 1;
    buffer = new char[num];
    memcpy(buffer, code.c_str(), num);
    return true;
}

void GLShaderProgram::use()
{
    glUseProgram(m_uShaderProgramID);
}

void GLShaderProgram::setb(const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(m_uShaderProgramID, name), (int)value);
}

void GLShaderProgram::seti(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(m_uShaderProgramID, name), (int)value);
}

void GLShaderProgram::setui(const char* name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(m_uShaderProgramID, name), value);
}

void GLShaderProgram::setf(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(m_uShaderProgramID, name), value);
}

void GLShaderProgram::set3f(const char* name, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(m_uShaderProgramID, name), value1, value2, value3);
}