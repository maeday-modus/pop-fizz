#pragma once

#include "datatype.hpp"

#include <stdint.h>
#include <vector>
#include <string>

namespace fizz
{
    enum class BufferType
    {
        VERTEX, INDEX, UNIFORM, PIXEL, STORAGE
    };

    enum class BufferMode
    {
        STATIC, DYNAMIC
    };

    struct BufferElement
    {
        std::string Name;
        DataType Type;
        bool Normalized;
        uint32_t Count;
    };

    class Buffer
    {
        uint32_t m_ID;
        BufferType m_Type;
        BufferMode m_Mode;
        uint32_t m_Size;

    public:
        Buffer(BufferType type, BufferMode mode);
        ~Buffer();
        void SetLayout(const std::vector<BufferElement>& layout);
        void SetData(void* data, uint32_t size);
        void InsertData(void* data, uint32_t offset, uint32_t size) const;

        inline void Bind() const;
        inline void Unbind() const;

        inline BufferType GetType() const { return m_Type; }
        inline BufferMode GetMode() const { return m_Mode; }
        inline uint32_t GetSize() const { return m_Size; }
    };
}
