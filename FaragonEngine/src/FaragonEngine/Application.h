#pragma once
#include "Core.h"

namespace FaragonEngine
{
	class FARAGON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
