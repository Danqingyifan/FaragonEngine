#pragma once
#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Events/WindowEvent.h"

#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "FaragonEngine/Renderer/Shader.h"
#include "FaragonEngine/Renderer/Buffer.h"
#include "FaragonEngine/Renderer/VertexArray.h"

#include "FaragonEngine/Renderer/Camera.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		// Camera
		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
	
}
