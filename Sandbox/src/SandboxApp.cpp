#include <FaragonEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public FaragonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (FaragonEngine::Input::IsKeyPressed(FA_KEY_TAB))
		{
			FA_CORE_INFO("Escape key pressed!");
		}
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



