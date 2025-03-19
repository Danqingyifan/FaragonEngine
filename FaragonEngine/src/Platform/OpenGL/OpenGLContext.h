#pragma once
#include "FaragonEngine/Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace FaragonEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext();
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

