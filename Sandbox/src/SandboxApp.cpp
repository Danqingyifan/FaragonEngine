#include <iostream>
#include <FaragonEngine.h>
class ExampleLayer : public FaragonEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {

    }

    void OnUpdate() override
    {
        std::cout << "ExampleLayer::OnUpdate" << std::endl;
    }

    void OnEvent(FaragonEngine::Event& event) override
    {
        std::cout << "ExampleLayer::OnEvent" << std::endl;
    }
};

class Sandbox : public FaragonEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new FaragonEngine::ImGuiLayer());
    }
    ~Sandbox()
    {

    }
    
};

FaragonEngine::Application* FaragonEngine::CreateApplication()
{

    return new Sandbox();
}



