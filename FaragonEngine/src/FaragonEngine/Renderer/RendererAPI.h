#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace FaragonEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		inline static API GetAPI() { return s_RenderAPI; }

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	private:
		static API s_RenderAPI;
	};
}

