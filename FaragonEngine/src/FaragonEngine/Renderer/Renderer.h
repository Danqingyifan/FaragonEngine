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
		static SceneData* s_SceneData;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(OrthographicCamera& camera);
		static void Flush();
		static void EndScene();

		static void DrawQuad(
			const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const float rotation = 0.0f, const glm::vec2& size = { 1.0f, 1.0f },
			const glm::vec4& color = { 1.0f, 1.0f , 1.0f, 1.0f },
			const Ref<Texture2D>& texture2D = WhiteTexture, const float tileFactor = 1.0f
		);
	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TexCoord;
			float TexIndex;
			float TilingFactor;
		};

		struct Renderer2DData
		{
			Ref<VertexArray> QuadVertexArray;
			Ref<VertexBuffer> QuadVertexBuffer;
			Ref<IndexBuffer> QuadIndexBuffer;
			Ref<Shader> QuadShader;
			
			const uint32_t MaxQuads = 10000;
			const uint32_t MaxVertices = MaxQuads * 4;
			const uint32_t MaxIndices = MaxQuads * 6;
			static const uint32_t MaxTextureSlots = 32;
			
			uint32_t QuadIndexCount = 0;
			QuadVertex* QuadVertexBufferBase = nullptr;
			QuadVertex* QuadVertexBufferPtr = nullptr;

			std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
			uint32_t TextureSlotIndex = 1; // 0 is reserved for white texture
		};
		static Renderer2DData s_Renderer2DData;

		static Ref<Texture2D> WhiteTexture;
	};
}

