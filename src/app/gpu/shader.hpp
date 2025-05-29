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
    
    struct ShaderPart
    {
        uint32_t ID;

        ShaderPart(const char* shaderCode, ShaderType type);
        ~ShaderPart();

        static uint32_t compileShader(const char* shaderCode, ShaderType type);
    };


    struct ShaderParam
    {
        ShaderType Type;
        const char* Source;
    };

    class Shader
    {
    public:
        Shader(const std::vector<ShaderParam>& shaderLayout);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_Program;
    };
}
