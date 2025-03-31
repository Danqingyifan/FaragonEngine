#include <FaragonEngine.h>
#include <FaragonEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PlatForm/OpenGL/OpenGLShader.h"

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


