#pragma once

#include "buffer.hpp"

#include <memory>

namespace fizz
{
    struct VertexArrayElement
    {
        DataType Type;
        bool Normalized;
        uint32_t Count;
    };

    class VertexArray
    {
        uint32_t m_ID;
        std::shared_ptr<Buffer> m_VertexBuffer;

    public:
        VertexArray();
        ~VertexArray();

        void AttachVertexBuffer(std::shared_ptr<Buffer> buffer);
        void SetLayout(const std::vector<VertexArrayElement>& layout);

        void Bind() const;
        void Unbind() const;
        inline std::shared_ptr<Buffer> GetVertexBuffer() const { return m_VertexBuffer; }
    };
}
