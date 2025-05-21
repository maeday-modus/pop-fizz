#include "logger.hpp"
#include "application.hpp"
#include "gfx/renderer.hpp"


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

    void Application::Run()
    {
        while (!m_Window.ShouldClose())
        {
            Renderer::ClearBuffers();

            m_Window.SwapPoll();
        }
    }

}

