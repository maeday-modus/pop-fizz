#include "datatype.hpp"

namespace fizz
{
    uint32_t DataTypeUtil::GetSize(const DataType& t)
    {   switch(t)
        {   // data type sizes
            case DataType::Uint:
                return sizeof(uint32_t);
            case DataType::Int:
                return sizeof(int);
            case DataType::Float:
                return sizeof(float);
            case DataType::Bool:
                return sizeof(bool);
            case DataType::Mat2:
                return 2*2*sizeof(float);
            case DataType::Mat3:
                return 3*3*sizeof(float);
            case DataType::Mat4:
                return 4*4*sizeof(float);
        }
    }
}
