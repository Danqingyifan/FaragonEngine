#include "FaragonPCH.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace FaragonEngine
{
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}