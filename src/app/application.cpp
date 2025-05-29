#include "logger.hpp"
#include "application.hpp"
#include "gpu/renderer.hpp"


namespace fizz
{
    Application::Application(const char* title, unsigned int width, unsigned int height)
        : m_Window(title, width, height)
    {
        // Check that window and renderer initialized properly
        Logger::ASSERT(Renderer::IsInitialized(), "Renderer failed to initialize!");

        // Set logger colors
        Logger::SetColor(LogLevel::ERROR, LoggerColor::RED);
        Logger::SetColor(LogLevel::WARN, LoggerColor::YELLOW);
        Logger::SetColor(LogLevel::INFO, LoggerColor::GREEN);

        // TODO: Make an event system (I want to try and do this in a functional programming way).
        // This is where we would set glfw callbacks
    }

    Application::~Application()
    {   // Detach all layers
        while (m_Layers.size() > 0)
            PopLayer();
    }

    void Application::Run()
    {
        while (!m_Window.ShouldClose())
        {   // Process layers
            for (std::shared_ptr<Layer> layer : m_Layers)
            {
                layer->Tick();
            }

            // Swap buffers and poll for events
            m_Window.SwapPoll();
        }
    }

    void Application::PushLayer(std::shared_ptr<Layer> layer)
    {
        layer->OnAttach();
        m_Layers.push_back(layer);
    }

    void Application::PopLayer()
    {
        std::shared_ptr<Layer> last = m_Layers[m_Layers.size() - 1];
        last->OnDetach();
        m_Layers.pop_back();
    }
}

