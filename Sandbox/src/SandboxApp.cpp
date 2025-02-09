#include <iostream>
#include <FaragonEngine.h>

class ExampleLayer : public FaragonEngine::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {

    }

    void OnUpdate() override
    {
        FA_INFO("ExampleLayer::OnUpdate");
    }

    void OnEvent(FaragonEngine::Event& event) override
    {
        FA_INFO("ExampleLayer::OnEvent");
    }
};

class Sandbox : public FaragonEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {

    }
    
};

FaragonEngine::Application* FaragonEngine::CreateApplication()
{
    return new Sandbox();
}


