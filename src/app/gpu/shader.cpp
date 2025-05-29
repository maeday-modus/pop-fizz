#include "shader.hpp"

#include "logger.hpp"
#include <glad/glad.h>

namespace fizz
{
    uint32_t ShaderPart::compileShader(const char* shaderCode, ShaderType type)
    {   // Resolve OpenGL type
        uint32_t glType;
        switch(type)
        {
            case ShaderType::VERTEX:
                glType = GL_VERTEX_SHADER;
                break;
            case ShaderType::GEOMETRY:
                glType = GL_GEOMETRY_SHADER;
                break;
            case ShaderType::FRAGMENT:
                glType = GL_FRAGMENT_SHADER;
                break;
            case ShaderType::COMPUTE:
                glType = GL_COMPUTE_SHADER;
                break;
        }

        uint32_t shader = glCreateShader(glType);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Logger::LogWARN(infoLog);
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
    Shader::Shader(const std::vector<ShaderParam>& shaderLayout)
    {   // compile shader parts
        std::vector<ShaderPart> shaders;
        shaders.reserve(shaderLayout.size());
        for (const ShaderParam& param : shaderLayout) {
            shaders.emplace_back(param.Source, param.Type);
        }

        // attach shader parts and link
        m_Program = glCreateProgram();
        for (ShaderPart& shader : shaders)
            glAttachShader(m_Program, shader.ID);
        glLinkProgram(m_Program);

        // check errs
        int success;
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
            Logger::LogWARN(infoLog);
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_Program);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_Program);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
}

