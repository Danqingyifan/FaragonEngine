#include <iostream>
#include <FaragonEngine.h>

class Sandbox : public FaragonEngine::Application
{
public:
    Sandbox()
    {

    }
    ~Sandbox()
    {

    }
    
};

FaragonEngine::Application* FaragonEngine::CreateApplication()
{
    return new Sandbox();
}

