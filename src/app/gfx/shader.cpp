#include "shader.hpp"
#include "../logger.hpp"

#include <glad/glad.h>

namespace fizz
{
    uint32_t compileShader(const char* shaderCode, uint32_t type)
    {
        uint32_t shader;
        shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderCode, nullptr);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Logger::LogERROR(infoLog);
        }

        return shader;
    }

    // ShaderPart class
    ShaderPart::ShaderPart(const char* shaderCode, uint32_t type)
        : ID(compileShader(shaderCode, type)) {}

    ShaderPart::~ShaderPart()
    {
        glDeleteShader(ID);
    }

    // Shader class
    Shader::Shader(const char* vertexCode, const char* fragmentCode)
    {
        ShaderPart vertShader(vertexCode, GL_VERTEX_SHADER);
        ShaderPart fragShader(fragmentCode, GL_FRAGMENT_SHADER);

        m_Program = glCreateProgram();
        glAttachShader(m_Program, vertShader.ID);
        glAttachShader(m_Program, fragShader.ID);

        int success;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
            Logger::LogERROR(infoLog);
        }
    }
}

