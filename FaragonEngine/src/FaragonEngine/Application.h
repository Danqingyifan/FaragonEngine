#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/WindowEvent.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	};

	//To be defined in CLIENT
	Application* CreateApplication();
	
}
