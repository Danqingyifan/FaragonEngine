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
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();

		inline static RendererAPI::API GetRenderAPI() { return  RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}

