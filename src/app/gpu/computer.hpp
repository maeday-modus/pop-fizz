#pragma once

#include "buffer.hpp"

namespace fizz
{
    class Computer
    {   // Static class with utilities for running compute shaders.
        // i.e. renderer but for compute stuff
    public:

        void DoThing(const Buffer& buffer);

    };
}
