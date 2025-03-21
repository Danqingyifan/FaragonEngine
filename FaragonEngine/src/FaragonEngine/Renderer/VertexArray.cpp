#include "FaragonPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FaragonEngine
{
	VertexArray* VertexArray::Create()
	{
		RenderAPI api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RenderAPI::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new OpenGLVertexArray();
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}
