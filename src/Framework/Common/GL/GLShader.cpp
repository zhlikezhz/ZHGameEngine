#include "GLShader.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace ZH;

GLShader::GLShader()
:m_uShaderProgramID(0)
{

}

GLShader::~GLShader()
{
    if (m_uShaderProgramID > 0) {
        glDeleteProgram(m_uShaderProgramID);
    }
}

GLShader* GLShader::createFromFile(const char* vertexFile, const char* fragmentFile)
{
    GLShader* program = new GLShader();

    char* vBuff = nullptr;
    char* fBuff = nullptr;
    if (program->loadFromFile(vertexFile, &vBuff) && program->loadFromFile(fragmentFile, &fBuff)) {
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

GLShader* GLShader::createFromMemory(const char* vBuff, const char* fBuff)
{
    GLShader* program = new GLShader();
    if (program->build(vBuff, fBuff)) {
        return program;
    }
    delete program;
    return nullptr;
}

bool GLShader::build(const char* vBuff, const char* fBuff)
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
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        glGetShaderInfoLog(fShader, 512, NULL, infoLog);
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

bool GLShader::loadFromFile(const char* filePath, char** buffer)
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
        return false;
    }
    int num = strlen(code.c_str()) + 1;
    *buffer = new char[num];
    memcpy(*buffer, code.c_str(), num);
    return true;
}

void GLShader::use()
{
    glUseProgram(m_uShaderProgramID);
}

void GLShader::setBool(const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(m_uShaderProgramID, name), (int)value);
}

void GLShader::setInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(m_uShaderProgramID, name), (int)value);
}

void GLShader::setUInt(const char* name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(m_uShaderProgramID, name), value);
}

void GLShader::setFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(m_uShaderProgramID, name), value);
}

void GLShader::set3Float(const char* name, float value1, float value2, float value3)
{
    glUniform3f(glGetUniformLocation(m_uShaderProgramID, name), value1, value2, value3);
}

void GLShader::setMat4(const char* name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_uShaderProgramID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}