#pragma once

namespace fizz
{
    class Renderer
    {
    public:
    
        static void Init();
        static void ClearBuffers();
        static void SetViewport(unsigned int x_0, unsigned int y_0, unsigned int x_1, unsigned int y_1);
        static void SetClearColor(double r, double g, double b);

        inline static bool IsInitialized() { return s_Initialized; }

    private:
        static bool s_Initialized;

    };
}
