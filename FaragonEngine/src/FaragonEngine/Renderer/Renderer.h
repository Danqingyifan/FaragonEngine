#pragma once

#include "RenderCommand.h"
#include "VertexArray.h"

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();

		inline static RendererAPI::API GetRenderAPI() { return  RendererAPI::GetAPI(); }
	};
}

