#include <memory>

#include "app/fizz.hpp"

class MyLayer : public fizz::Layer
{   // Game Data
    std::shared_ptr<fizz::VertexArray> m_VertexArray;
    std::shared_ptr<fizz::Shader> m_Shader;

public:
    void OnAttach()
    {
        fizz::Logger::LogINFO("==> Attached MyLayer!");

        // Set up shader
        m_Shader = std::make_shared<fizz::Shader>(std::vector<fizz::ShaderParam>({
            fizz::ShaderParam{
                fizz::ShaderType::VERTEX,
                R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)"
            },
            fizz::ShaderParam{
                fizz::ShaderType::FRAGMENT,
                R"(#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)"
            }
        }));

        // Initialize vertex array
        std::vector<float> vertData {
           -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0,  0.5, 0.0,
        };
        m_VertexArray = std::make_shared<fizz::VertexArray>();
        std::shared_ptr<fizz::Buffer> VBO = 
            std::make_shared<fizz::Buffer>(fizz::BufferType::VERTEX, fizz::BufferMode::STATIC);
        m_VertexArray->AttachVertexBuffer(VBO);

        // Setup actual buffer data
        VBO->SetData(vertData.data(), sizeof(vertData[0]), vertData.size());
        m_VertexArray->SetLayout({
            fizz::VertexArrayElement{
                // Position
                fizz::DataType::Float, false, 3
            }
        });
    }

    void OnDetach()
    {
        fizz::Logger::LogINFO("==> Detached MyLayer.");
    }

    void Tick()
    {   // Use the shader and render the vertex buffer
        fizz::Renderer::ClearBuffers();
        m_Shader->Bind();
        fizz::Renderer::DrawVertexArray(m_VertexArray);
    }
};

class MyApp : public fizz::Application
{
public:
    MyApp()
        : Application("C++ Game Engine Demo", 800, 600)
    {
        fizz::Renderer::SetClearColor(0.1, 0.2, 0.2);
        PushLayer(std::make_shared<MyLayer>());
    }

};

int main()
{
    MyApp app;

    app.Run();
}
