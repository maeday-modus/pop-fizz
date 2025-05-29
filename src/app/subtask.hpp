#pragma once

#include "event.hpp"

namespace fizz
{
    class Subtask
    {
    public:
        Subtask();
        virtual ~Subtask();

        virtual void Tick();
        virtual void OnEvent(const Event& e);
    };
}
