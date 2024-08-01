#include "FaragonPCH.h"

#include "Application.h"
#include "FaragonEngine/Events/ApplicationEvent.h"
#include "FaragonEngine/Log.h"

namespace FaragonEngine
{
    Application::Application()
    {

    }
    Application::~Application()
    {

    }
    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        std::cout << e.ToString();

        while (true)
        {

        }
    }
}
