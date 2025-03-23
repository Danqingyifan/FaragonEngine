#include "FaragonPCH.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
namespace FaragonEngine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}

	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}
