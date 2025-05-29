#include "buffer.hpp"
#include "logger.hpp"

#include <glad/glad.h>

namespace fizz
{
    static uint32_t GetGLType(const BufferType& type)
    {
        switch(type)
        {   // convert to opengl buffer "mode" (type/location)
            case BufferType::VERTEX:
                return GL_ARRAY_BUFFER;
            case BufferType::INDEX:
                return GL_ELEMENT_ARRAY_BUFFER;
            case BufferType::UNIFORM:
                return GL_UNIFORM_BUFFER;
            case BufferType::PIXEL:
                return GL_TEXTURE_BUFFER;
            case BufferType::STORAGE:
                return GL_SHADER_STORAGE_BUFFER;
        }
    }

    static uint32_t GetGLMode(const BufferMode& mode)
    {
        switch(mode)
        {   // get the opengl "usage" (i think mode works better here)
            case BufferMode::STATIC:
                return GL_STATIC_DRAW;
            case BufferMode::DYNAMIC:
                return GL_DYNAMIC_DRAW;
        }
    }

    static uint32_t GetGLDataType(const DataType& type)
    {
        switch (type)
        {
            case DataType::Uint:
                return GL_UNSIGNED_INT;
            case DataType::Int:
                return GL_INT;
            case DataType::Bool:
                return GL_BOOL;
            case DataType::Float: case DataType::Mat2: case DataType::Mat3: case DataType::Mat4:
                return GL_FLOAT;
        }
    }

    Buffer::Buffer(BufferType type, BufferMode mode)
        : m_Type(type), m_Mode(mode), m_ElementSize(0), m_Count(0)
    {   // create opengl buffer object
        glCreateBuffers(1, &m_ID);
    }

    Buffer::~Buffer()
    {   // free vram
        glDeleteBuffers(1, &m_ID);
    }


    void Buffer::SetData(void* data, uint32_t elementSize, uint32_t count)
    {   // Set new size
        m_ElementSize = elementSize;
        m_Count = count;

        Bind();
        glBufferData(GetGLType(m_Type), m_Count * m_ElementSize, data, GetGLMode(m_Mode));
    }

    void Buffer::InsertData(void* data, uint32_t offset, uint32_t count) const
    {   // check size
        Logger::ASSERT(GetSize() > 0,
                "Cannot insert data into empty buffer");
        Logger::ASSERT(offset + count * m_ElementSize <= GetSize(),
                "Requested buffer insertion would overflow buffer. Data not sent to GPU.");

        Bind();
        glBufferSubData(GetGLType(m_Type), offset, count * m_ElementSize, data);
    }

    void Buffer::Bind() const
    {
        glBindBuffer(GetGLType(m_Type), m_ID);
    }

    void Buffer::BindAs(const BufferType& type) const
    {   // Hopefully useful for using compute shader output as vertex data
        glBindBuffer(GetGLType(type), m_ID);
    }

    void Buffer::Unbind() const
    {
        glBindBuffer(GetGLType(m_Type), 0);
    }
}
