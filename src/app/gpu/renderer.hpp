#pragma once

#include <memory>

#include "vertexarray.hpp"

namespace fizz
{
    class Renderer
    {
    public:
    
        static void Init();
        static void SetViewport(unsigned int x_0, unsigned int y_0, unsigned int x_1, unsigned int y_1);
        static void SetClearColor(double r, double g, double b);

        // DRAW CALLS
        static void ClearBuffers();
        static void DrawVertexArray(std::shared_ptr<VertexArray> mesh);

        inline static bool IsInitialized() { return s_Initialized; }

    private:
        static bool s_Initialized;

    };
}
