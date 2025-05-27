#pragma once

#include <stdint.h>

namespace fizz
{
    enum class DataType
    {
        Uint, Int, Float, Bool,
        Mat2, Mat3, Mat4
    };

    struct DataTypeUtil
    {
        static uint32_t GetSize(const DataType& t);
    };
}
