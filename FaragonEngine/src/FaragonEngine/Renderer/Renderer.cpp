#include "FaragonPCH.h"

#include "Renderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FaragonEngine
{
	//////////////////////////////////
	////////////Renderer//////////////
	//////////////////////////////////

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform /*= glm::mat4(1.0f)*/)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
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

	Renderer2D::Renderer2DStorage* Renderer2D::s_Renderer2DData = new Renderer2D::Renderer2DStorage;

	void Renderer2D::Init()
	{
		// White Texture
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DData->WhiteTexture = Texture2D::Create(1, 1, &whiteTextureData, sizeof(uint32_t));

		s_Renderer2DData->QuadVertexArray = VertexArray::Create();
		// Add vertex buffer and layout
		BufferLayout layout = {
			{ "a_Pos",ShaderDataType::Float3},
			{ "a_Color",ShaderDataType::Float4},
			{ "a_TexCoord",ShaderDataType::Float2}
		};

		float vertices[] = {
			// positions		// colors               //TexCoords
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,	1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f
		};

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout(layout);

		s_Renderer2DData->QuadVertexArray->AddVertexBuffer(vertexBuffer);

		// Add index buffer
		uint32_t indices[] = { 0, 1, 2 , 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		s_Renderer2DData->QuadVertexArray->SetIndexBuffer(indexBuffer);

		// Add shaders
		s_Renderer2DData->Shader = Shader::Create("assets/shaders/TextureShader.glsl");
	}

	void Renderer2D::ShutDown()
	{
		delete s_Renderer2DData;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Renderer2DData->Shader->Bind();
		s_Renderer2DData->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Renderer2DData->Shader->SetMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture2D)
	{
		s_Renderer2DData->Shader->SetInt("u_Texture", 0);

		texture2D->Bind();

		s_Renderer2DData->Shader->SetFloat4("u_Color", color);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		glm::mat4 transform = translate * rotate * scale;

		s_Renderer2DData->Shader->SetMat4("u_Transform", transform);

		s_Renderer2DData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData->QuadVertexArray);
	}
}