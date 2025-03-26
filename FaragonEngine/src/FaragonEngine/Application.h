#pragma once
#include "FaragonEngine/Core/Core.h"
#include "FaragonEngine/Core/Window.h"
#include "FaragonEngine/Core/LayerStack.h"

#include "FaragonEngine/Events/Event.h"
#include "FaragonEngine/Events/WindowEvent.h"

#include "FaragonEngine/ImGui/ImGuiLayer.h"

namespace FaragonEngine
{
	class FARAGON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
	
}
