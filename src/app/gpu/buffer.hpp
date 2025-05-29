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

    class Buffer
    {
        uint32_t m_ID;
        BufferType m_Type;
        BufferMode m_Mode;
        uint32_t m_ElementSize;
        uint32_t m_Count;

    public:
        Buffer(BufferType type, BufferMode mode);
        ~Buffer();
        void SetData(void* data, uint32_t elementSize, uint32_t count);
        void InsertData(void* data, uint32_t offset, uint32_t count) const;

        void Bind() const;
        void BindAs(const BufferType& type) const;
        void Unbind() const;

        inline BufferType GetType() const { return m_Type; }
        inline BufferMode GetMode() const { return m_Mode; }
        inline uint32_t GetCount() const { return m_Count; }
        inline uint32_t GetSize() const { return m_Count * m_ElementSize; }
        inline uint32_t GetRawID() const { return m_ID; }
    };
}
