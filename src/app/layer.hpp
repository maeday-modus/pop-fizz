#pragma once

#include "event.hpp"

namespace fizz
{
    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void Tick() {}
        virtual void OnEvent(const Event& e) {}
    };
}
