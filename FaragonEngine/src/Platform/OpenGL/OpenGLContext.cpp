#include "FaragonPCH.h"
#include "OpenGLContext.h"
#include "FaragonEngine/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FaragonEngine
{
	OpenGLContext::OpenGLContext()
	{

	}

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		FA_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FA_CORE_ASSERT(status, "Could not initialize GLAD!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}