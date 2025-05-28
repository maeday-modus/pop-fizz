#pragma once

#include <stdint.h>
#include <vector>

namespace fizz
{
    enum class ShaderType
    {
        VERTEX, GEOMETRY, FRAGMENT,
        COMPUTE
    };
    
    class ShaderPart
    {
    public:
        ShaderPart(const char* shaderCode, ShaderType type);
        ~ShaderPart();

        static uint32_t compileShader(const char* shaderCode, ShaderType type);
        
        uint32_t ID;
    };


    struct ShaderParam
    {
        ShaderType Type;
        const char* Source;
    };

    class Shader
    {
    public:
        Shader(std::vector<ShaderParam> shaderLayout);

    private:
        uint32_t m_Program;
    };
}
