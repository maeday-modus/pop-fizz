
#include "window.h"
#include "gfx/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
                // For whatever reason, this causes a runtime error where the window fails to create.
                //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            }
        }
    };

    bool GLFW::s_Initialized = false;


    Window::Window(const char* title, unsigned int width, unsigned int height)
    {
        GLFW::Init();

        m_NativeWindow = glfwCreateWindow(100, 100, m_Title, nullptr, nullptr);
        if (m_NativeWindow == nullptr)
        {
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_NativeWindow);

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
}

