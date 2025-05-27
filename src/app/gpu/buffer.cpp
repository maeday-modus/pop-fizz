#include "buffer.hpp"
#include "logger.hpp"

#include <glad/glad.h>

namespace fizz
{
    static uint32_t GetGLType(const BufferType& type)
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

    static uint32_t GetGLMode(const BufferMode& mode)
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
        : m_Type(type), m_Mode(mode), m_Size(0)
    {   // create opengl buffer object
        glCreateBuffers(1, &m_ID);
    }

    Buffer::~Buffer()
    {   // free vram
        glDeleteBuffers(1, &m_ID);
    }

    void Buffer::SetLayout(const std::vector<BufferElement>& layout)
    {   // calculate stride
        uint32_t stride;
        for (const BufferElement& element : layout)
            stride += element.Count * DataTypeUtil::GetSize(element.Type);

        Bind();
        // map elements
        int i = 0;
        uint32_t offset = 0;
        for (const BufferElement& element : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.Count, GetGLDataType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE, stride, (void*)offset);
            i++;
        }
    }

    void Buffer::SetData(void* data, uint32_t size)
    {   // Set new size
        m_Size = size;

        Bind();
        glBufferData(GetGLType(m_Type), m_Size, data, GetGLMode(m_Mode));
    }

    void Buffer::InsertData(void* data, uint32_t offset, uint32_t size) const
    {   // check size
        if (offset + size > m_Size)
        {
            Logger::LogWARN("Requested buffer insertion would overflow buffer. Data not sent to GPU.");
            return;
        }

        Bind();
        glBufferSubData(GetGLType(m_Type), offset, size, data);
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
