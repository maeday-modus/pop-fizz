#include "window.hpp"
#include "gpu/renderer.hpp"
#include "logger.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace fizz
{
    class GLFW
    {
        static bool s_Initialized;

    public:
        static void Init()
        {
            if (!s_Initialized)
            {
                s_Initialized = true;
                glfwInit();
                
                // Window hints probably don't need to be here, but This will make all of our windows have the same hints
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                // For whatever reason, this causes a runtime error where the window fails to create.
                //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            }
        }
    };

    bool GLFW::s_Initialized = false;


    Window::Window(const char* title, unsigned int width, unsigned int height)
        : m_Title(title), m_Width(width), m_Height(height)
    {
        GLFW::Init();

        m_NativeWindow = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
        if (m_NativeWindow == nullptr)
        {
            glfwTerminate();
            Logger::LogERROR("WINDOW: Could not create glfw window!");
        }
        glfwMakeContextCurrent(m_NativeWindow);
        glfwSetFramebufferSizeCallback(m_NativeWindow, Window::ResizeCallback);

        Renderer::Init();
        Renderer::SetViewport(0, 0, m_Width, m_Height);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_NativeWindow);
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_NativeWindow);
    }

    void Window::SwapPoll() const
    {
        glfwSwapBuffers(m_NativeWindow);
        glfwPollEvents();
    }

    void Window::ResizeCallback(GLFWwindow* window, int width, int height)
    {
        Renderer::SetViewport(0, 0, width, height);
    }
}

