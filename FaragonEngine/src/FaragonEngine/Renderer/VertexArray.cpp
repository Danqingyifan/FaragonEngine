#include "FaragonPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FaragonEngine
{
	Ref<VertexArray> VertexArray::Create()
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}
