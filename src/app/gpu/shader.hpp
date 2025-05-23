#pragma once

#include <stdint.h>

namespace fizz
{
    enum class ShaderType
    {
        VERTEX, GEOMETRY, FRAGMENT,
        COMPUTE
    };

    static uint32_t compileShader(const char* shaderCode, ShaderType type);
    
    // RENDERING SHADERS
    class ShaderPart
    {
    public:
        ShaderPart(const char* shaderCode, ShaderType type);
        ~ShaderPart();
        
        uint32_t ID;
    };

    class Shader
    {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);

    private:
        uint32_t m_Program;
    };

    // COMPUTE SHADER
    class ComputeShader
    {
    public:
        ComputeShader(const char* shaderSource);

    private:
        uint32_t m_Program;
    };
}
