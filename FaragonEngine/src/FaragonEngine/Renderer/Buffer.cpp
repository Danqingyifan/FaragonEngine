#include "FaragonPCH.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
namespace FaragonEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}

	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}
