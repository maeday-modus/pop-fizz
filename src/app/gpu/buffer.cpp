#include "buffer.hpp"

#include <glad/glad.h>

namespace fizz
{
    static uint32_t GetGLType(BufferType type)
    {
        uint32_t r;
        switch(type)
        {   // convert to opengl buffer "mode" (type/location)
            case BufferType::VERTEX:
                r = GL_ARRAY_BUFFER;
            case BufferType::INDEX:
                r = GL_ELEMENT_ARRAY_BUFFER;
            case BufferType::UNIFORM:
                r = GL_UNIFORM_BUFFER;
            case BufferType::PIXEL:
                r = GL_TEXTURE_BUFFER;
            case BufferType::STORAGE:
                r = GL_SHADER_STORAGE_BUFFER;
        }
        return r;
    }

    static uint32_t GetGLMode(BufferMode mode)
    {
        uint32_t r;
        switch(mode)
        {   // get the opengl "usage" (i think mode works better here)
            case BufferMode::STATIC:
                r = GL_STATIC_DRAW;
            case BufferMode::DYNAMIC:
                r = GL_DYNAMIC_DRAW;
        }
        return r;
    }
    
    Buffer::Buffer(BufferType type, BufferMode mode, uint32_t size)
        : m_Type(type), m_Mode(mode), m_Size(size)
    {   // Resolve OpenGL types
        uint32_t glType = GetGLType(type);
        uint32_t glMode = GetGLMode(mode);

        // create opengl buffer object
        glCreateBuffers(1, &m_ID);
        glBufferData(glType, size, nullptr, glMode);
    }

    inline void Buffer::Bind() const
    {
        glBindBuffer(GetGLType(m_Type), m_ID);
    }

    inline void Buffer::Unbind() const
    {
        glBindBuffer(GetGLType(m_Type), 0);
    }
}
