#include "FaragonPCH.h"
#include "Framebuffer.h"

#include "FaragonEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace FaragonEngine 
{

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetRenderAPI())
		{
		case RendererAPI::API::None:    FA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		FA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}