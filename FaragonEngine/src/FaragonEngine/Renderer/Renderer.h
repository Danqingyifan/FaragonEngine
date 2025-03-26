#pragma once

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
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

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(
			const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const float rotation = 0.0f, const glm::vec2& size = { 1.0f, 1.0f }, 
			const glm::vec4& color = { 1.0f, 1.0f , 1.0f, 1.0f },
			const Ref<Texture2D>& texture2D = s_Renderer2DData->WhiteTexture, const float tileFactor = 1.0f
		);

	private:
		struct Renderer2DStorage
		{
			Ref<VertexArray> QuadVertexArray;
			Ref<Shader> Shader;
			Ref<Texture2D> WhiteTexture;
		};
		static Renderer2DStorage* s_Renderer2DData;
	};
}

