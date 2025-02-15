#include "FaragonPCH.h"

#include "Application.h"
#include "FaragonEngine/Log.h"
#include "FaragonEngine/Events/WindowEvent.h"

#include <glad/glad.h>

namespace FaragonEngine
{   
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }
    Application::~Application()
    {

    }

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        FA_INFO("Application Event:{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it!= m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.GetIsHandled())
                break;
        }

	}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }
}
