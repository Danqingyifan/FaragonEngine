#include "FaragonPCH.h"

#include "Renderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FaragonEngine
{
	//////////////////////////////////
	////////////Renderer//////////////
	//////////////////////////////////

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform /*= glm::mat4(1.0f)*/)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	//////////////////////////////////
	////////////Renderer2D////////////
	//////////////////////////////////

	Renderer2D::Renderer2DData Renderer2D::s_Renderer2DData;

	Ref<Texture2D> Renderer2D::WhiteTexture;

	void Renderer2D::Init()
	{
		uint32_t whiteTextureData = 0xffffffff;
		WhiteTexture = Texture2D::Create(1, 1, &whiteTextureData, sizeof(uint32_t));

		s_Renderer2DData.QuadVertexArray = VertexArray::Create();
		BufferLayout layout = {
			{ "a_Pos",ShaderDataType::Float3},
			{ "a_Color",ShaderDataType::Float4},
			{ "a_TexCoord",ShaderDataType::Float2},
			{ "a_TexIndex",ShaderDataType::Float},
			{ "a_TilingFactor",ShaderDataType::Float}
		};

		// Add vertex buffer
		s_Renderer2DData.QuadVertexBuffer = VertexBuffer::Create(s_Renderer2DData.MaxVertices * sizeof(QuadVertex));
		s_Renderer2DData.QuadVertexBuffer->SetLayout(layout);
		s_Renderer2DData.QuadVertexBufferBase = new QuadVertex[s_Renderer2DData.MaxVertices];
		s_Renderer2DData.QuadVertexArray->AddVertexBuffer(s_Renderer2DData.QuadVertexBuffer);

		// Add index buffer
		uint32_t* indices = new uint32_t[s_Renderer2DData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Renderer2DData.MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}
		s_Renderer2DData.QuadIndexBuffer = IndexBuffer::Create(indices, s_Renderer2DData.MaxIndices);
		s_Renderer2DData.QuadVertexArray->SetIndexBuffer(s_Renderer2DData.QuadIndexBuffer);
		delete[] indices;

		// Add shaders
		s_Renderer2DData.QuadShader = Shader::Create("assets/shaders/TextureShader.glsl");

		s_Renderer2DData.TextureSlots[0] = WhiteTexture;
	}

	void Renderer2D::ShutDown()
	{
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Renderer2DData.QuadShader->Bind();
		s_Renderer2DData.QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Renderer2DData.QuadShader->SetMat4("u_Transform", glm::mat4(1.0f));

		StartBatch();
	}

	void Renderer2D::StartBatch()
	{
		s_Renderer2DData.QuadIndexCount = 0;
		s_Renderer2DData.QuadVertexBufferPtr = s_Renderer2DData.QuadVertexBufferBase;
		s_Renderer2DData.TextureSlotIndex = 1;
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Renderer2DData.QuadVertexBufferPtr - (uint8_t*)s_Renderer2DData.QuadVertexBufferBase);
		s_Renderer2DData.QuadVertexBuffer->SetData(s_Renderer2DData.QuadVertexBufferBase, dataSize);

		// Bind textures
		for (uint32_t i = 0; i < s_Renderer2DData.TextureSlotIndex; i++)
			s_Renderer2DData.TextureSlots[i]->Bind(i);

		s_Renderer2DData.QuadShader->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData.QuadVertexArray, s_Renderer2DData.QuadIndexCount);

		s_Renderer2DData.Stats.DrawCalls++;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Renderer2DData.QuadVertexBufferPtr - (uint8_t*)s_Renderer2DData.QuadVertexBufferBase;
		s_Renderer2DData.QuadVertexBuffer->SetData(s_Renderer2DData.QuadVertexBufferBase, dataSize);
		Flush();
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuadHelper(position, rotation, size, color, WhiteTexture, 1.0f);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture2D, const float tileFactor, const glm::vec4& tintColor)
	{
		DrawQuadHelper(position, rotation, size, tintColor, texture2D, tileFactor);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<SubTexture2D>& subTexture2D, const float tileFactor, const glm::vec4& tintColor)
	{
		DrawQuadHelper(position, rotation, size, tintColor, subTexture2D, tileFactor);
	}


	// Private
	void Renderer2D::DrawQuadHelper(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture2D, const float tileFactor)
	{
		float textureIndex = 0.0f;

		if (s_Renderer2DData.QuadIndexCount >= s_Renderer2DData.MaxIndices)
		{
			NextBatch();
		}

		for (uint32_t i = 1; i < s_Renderer2DData.TextureSlotIndex; i++)
		{
			if (s_Renderer2DData.TextureSlots[i]->GetRendererID() == texture2D->GetRendererID())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f && texture2D->GetRendererID() != WhiteTexture->GetRendererID())
		{
			if (s_Renderer2DData.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				NextBatch();
			}
			textureIndex = (float)s_Renderer2DData.TextureSlotIndex;
			s_Renderer2DData.TextureSlots[s_Renderer2DData.TextureSlotIndex] = texture2D;
			s_Renderer2DData.TextureSlotIndex++;
		}

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		glm::mat4 transform = translate * rotate * scale;

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		constexpr size_t quadVertexCount = 4;

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[i];
			s_Renderer2DData.QuadVertexBufferPtr->Color = color;
			s_Renderer2DData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Renderer2DData.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tileFactor;
			s_Renderer2DData.QuadVertexBufferPtr++;
		}

		s_Renderer2DData.QuadIndexCount += 6;

		s_Renderer2DData.Stats.QuadCount++;

		int samplers[s_Renderer2DData.MaxTextureSlots] = { 0 };
		for (uint32_t i = 0; i < s_Renderer2DData.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		s_Renderer2DData.QuadShader->SetIntArray("u_Textures", samplers, s_Renderer2DData.MaxTextureSlots);
	}

	void Renderer2D::DrawQuadHelper(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color, const Ref<SubTexture2D>& subTexture2D, const float tileFactor)
	{
		float textureIndex = 0.0f;

		Ref<Texture2D> texture2D = subTexture2D->GetTexture();
		const glm::vec2* textureCoords = subTexture2D->GetTexCoords();

		if (s_Renderer2DData.QuadIndexCount >= s_Renderer2DData.MaxIndices)
		{
			NextBatch();
		}

		for (uint32_t i = 1; i < s_Renderer2DData.TextureSlotIndex; i++)
		{
			if (s_Renderer2DData.TextureSlots[i]->GetRendererID() == texture2D->GetRendererID())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f && texture2D->GetRendererID() != WhiteTexture->GetRendererID())
		{
			if (s_Renderer2DData.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
			{
				NextBatch();
			}

			textureIndex = (float)s_Renderer2DData.TextureSlotIndex;
			s_Renderer2DData.TextureSlots[s_Renderer2DData.TextureSlotIndex] = texture2D;
			s_Renderer2DData.TextureSlotIndex++;
		}

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		glm::mat4 transform = translate * rotate * scale;

		constexpr size_t quadVertexCount = 4;

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Renderer2DData.QuadVertexBufferPtr->Position = transform * s_Renderer2DData.QuadVertexPositions[i];
			s_Renderer2DData.QuadVertexBufferPtr->Color = color;
			s_Renderer2DData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Renderer2DData.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Renderer2DData.QuadVertexBufferPtr->TilingFactor = tileFactor;
			s_Renderer2DData.QuadVertexBufferPtr++;
		}

		s_Renderer2DData.QuadIndexCount += 6;

		s_Renderer2DData.Stats.QuadCount++;

		int samplers[s_Renderer2DData.MaxTextureSlots] = { 0 };
		for (uint32_t i = 0; i < s_Renderer2DData.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		s_Renderer2DData.QuadShader->SetIntArray("u_Textures", samplers, s_Renderer2DData.MaxTextureSlots);
	}
}