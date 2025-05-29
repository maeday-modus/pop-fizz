#include "vertexarray.hpp"
#include "gpu/buffer.hpp"
#include "logger.hpp"

#include <glad/glad.h>

namespace fizz
{
    // UTIL
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

    // VERTEX ARRAY START
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_ID);
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VertexArray::AttachVertexBuffer(std::shared_ptr<Buffer> buffer)
    {   // Verify the correct type
        if (buffer->GetType() != BufferType::VERTEX)
            Logger::LogWARN("VERTEX ARRAY: Attaching buffer that is not of type VERTEX");

        Bind();
        m_VertexBuffer = buffer;
        m_VertexBuffer->BindAs(BufferType::VERTEX);
    }

    void VertexArray::SetLayout(const std::vector<VertexArrayElement>& layout)
    {   // calculate stride
        uint32_t stride = 0;
        for (const VertexArrayElement& element : layout)
            stride += element.Count * DataTypeUtil::GetSize(element.Type);

        Bind();
        m_VertexBuffer->BindAs(BufferType::VERTEX);
        // map elements
        int i = 0;
        uint32_t offset = 0;
        for (const VertexArrayElement& element : layout)
        {
            glVertexAttribPointer(i, element.Count, GetGLDataType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, stride, (void*)offset);
            glEnableVertexAttribArray(i);
            i++;
        }
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
