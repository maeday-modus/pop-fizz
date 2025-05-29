#pragma once

#include "window.hpp"
#include "layer.hpp"

#include <vector>
#include <memory>

namespace fizz
{
    class Application
    {
        std::vector<std::shared_ptr<Layer>> m_Layers;
        Window m_Window;

    public:

        Application(const char* title, unsigned int width, unsigned int height);
        ~Application();

        void PushLayer(std::shared_ptr<Layer> layer);
        void PopLayer();

        void Run();
    };
}

