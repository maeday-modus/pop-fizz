#pragma once

#include <stdint.h>

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

    class Buffer
    {
        uint32_t m_ID;
        BufferType m_Type;
        BufferMode m_Mode;
        uint32_t m_Size;

    public:
        Buffer(BufferType type, BufferMode mode, uint32_t size);
        inline void Bind() const;
        inline void Unbind() const;

        inline BufferType GetType() const { return m_Type; }
        inline BufferMode GetMode() const { return m_Mode; }
        inline uint32_t GetSize() const { return m_Size; }
    };
}
