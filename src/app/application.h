#pragma once

#include <string>
#include <memory>

#include "logger.h"
#include "window.h"

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

