#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertPath, const std::string& fragPath): _vertShader{}, _fragShader{}, _id{}, _vertID{}, _fragID{}
{
    if(!vertPath.empty()) _vertShader = readFile(vertPath);
    
    if (!fragPath.empty()) _fragShader = readFile(fragPath);
}

void Shader::createShaders()
{
    _id = glCreateProgram();
    _vertID = compileShader(GL_VERTEX_SHADER, _vertShader);
    _fragID = compileShader(GL_FRAGMENT_SHADER, _fragShader);

    glAttachShader(_id, _vertID);
    glAttachShader(_id, _fragID);
    glLinkProgram(_id);
    glValidateProgram(_id);

    glDeleteShader(_vertID);
    glDeleteShader(_fragID);
}

void Shader::useShader()
{
    glUseProgram(_id);
}

void Shader::setUniform(const char* name, const Maths::Matrix4& matrix) const
{
    int location = glGetUniformLocation(_id, name);
    if (location != -1)
        glUniformMatrix4fv(location, 1, false, matrix.toOpenGL());
}

void Shader::setUniform(const char* name, const float value) const
{
    int location = glGetUniformLocation(_id, name);
    if (location != -1)
        glUniform1f(location, value);
}

void Shader::setUniform(const char* name, const int value) const
{
    int location = glGetUniformLocation(_id, name);
    if (location != -1)
        glUniform1i(location, value);
}

void Shader::setUniform(const char* name, const Maths::Vector3& vector) const
{
    int location = glGetUniformLocation(_id, name);
    if (location != -1)
        glUniform3f(location, vector.getX(), vector.getY(), vector.getZ());
}

void Shader::setUniform(const char* name, const Maths::Vector4& vector) const
{
    int location = glGetUniformLocation(_id, name);
    if (location != -1)
        glUniform4f(location, vector.getX(), vector.getY(), vector.getZ(), vector.getW());
}

const std::string Shader::readFile(const std::string& path) const
{
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (in)
    {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return(contents.str());
    }
	return std::string();
}

const unsigned int Shader::compileShader(GLenum type, const std::string& shader)
{
    //std::cout << source << std::endl;
    unsigned int id = glCreateShader(type);
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error handling
    int result{};
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "FAILED TO COMPILE SHADER " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " SHADER" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
