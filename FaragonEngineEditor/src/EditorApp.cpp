#include <FaragonEngine.h>

#include <FaragonEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace FaragonEngine 
{
	class EditorApp : public Application
	{
	public:
		EditorApp()
		{
			PushLayer(new EditorLayer());
		}
		~EditorApp()
		{
			
		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}


