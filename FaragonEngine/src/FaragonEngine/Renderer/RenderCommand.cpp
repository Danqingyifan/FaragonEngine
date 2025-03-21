#include "FaragonPCH.h"
#include "RenderCommand.h"

#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace FaragonEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
	