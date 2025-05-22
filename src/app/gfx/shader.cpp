#include "shader.hpp"
#include "../logger.hpp"

#include <glad/glad.h>

namespace fizz
{
    uint32_t compileShader(const char* shaderCode, ShaderType type)
    {   // Resolve OpenGL type
        uint32_t glType;
        switch(type)
        {
            case ShaderType::VERTEX:
                glType = GL_VERTEX_SHADER;
            case ShaderType::GEOMETRY:
                glType = GL_GEOMETRY_SHADER;
            case ShaderType::FRAGMENT:
                glType = GL_FRAGMENT_SHADER;
            case ShaderType::COMPUTE:
                glType = GL_COMPUTE_SHADER;
        }

        uint32_t shader;
        shader = glCreateShader(glType);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);

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
    ShaderPart::ShaderPart(const char* shaderCode, ShaderType type)
        : ID(compileShader(shaderCode, type)) {}

    ShaderPart::~ShaderPart()
    {
        glDeleteShader(ID);
    }

    // Shader class
    Shader::Shader(const char* vertexCode, const char* fragmentCode)
    {
        ShaderPart vertShader(vertexCode, ShaderType::VERTEX);
        ShaderPart fragShader(fragmentCode, ShaderType::FRAGMENT);

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

    // ComputeShader class
    ComputeShader::ComputeShader(const char* shaderSource)
    {
    }
}

