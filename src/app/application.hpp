#pragma once

#include "window.hpp"

namespace fizz
{
    class Application
    {
    public:

        Application(const char* title, unsigned int width, unsigned int height);
        ~Application() = default;

        void Run();

    private:
        Window m_Window;
    };
}

