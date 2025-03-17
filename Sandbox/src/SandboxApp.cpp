#include <FaragonEngine.h>

class ExampleLayer : public FaragonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		auto cam = camera(10.0f, glm::vec2(0.0f, 0.0f));
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



