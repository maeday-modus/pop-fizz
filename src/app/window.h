#pragma once


typedef struct GLFWwindow GLFWwindow;

namespace fizz
{
    class Window
    {
    public:
        Window(const char* title, unsigned int width, unsigned int height);
        ~Window();

        bool ShouldClose() const;
        void SwapPoll() const;

    private:
        const char* m_Title;
        unsigned int m_Width, m_Height;
        GLFWwindow* m_NativeWindow;
    };
}

