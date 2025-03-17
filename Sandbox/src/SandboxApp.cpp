#include <iostream>
#include <FaragonEngine.h>

class Sandbox : public FaragonEngine::Application
{
public:
	Sandbox()
	{
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



