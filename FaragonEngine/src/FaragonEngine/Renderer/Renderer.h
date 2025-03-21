#pragma once

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Camera.h"

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();

		inline static RendererAPI::API GetRenderAPI() { return  RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}

