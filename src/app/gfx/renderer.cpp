#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace fizz
{
    bool Renderer::s_Initialized = false;

    void Renderer::Init()
    {
        // Initialize glad
        if (!s_Initialized)
        {
            s_Initialized = true;
            
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                s_Initialized = false;
            }
        }
    }

    void Renderer::ClearBuffers()
    {
        // Could have a better API for choosing which, but we're not writing a AAA renderer, sooo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void Renderer::SetViewport(unsigned int x_0, unsigned int y_0, unsigned int x_1, unsigned int y_1)
    {
       glViewport(x_0, y_0, x_1, y_1);
    }

    void Renderer::SetClearColor(double r, double g, double b)
    {
        glClearColor(r, g, b, 1.0);
    }
}
