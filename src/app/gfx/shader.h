#pragma once

#include <stdint.h>

namespace fizz
{
    
    static uint32_t compileShader(const char* shaderCode);

    class ShaderPart
    {
    public:
        ShaderPart(const char* shaderCode, uint32_t type);
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

}
