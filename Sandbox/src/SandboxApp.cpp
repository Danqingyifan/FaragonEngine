#include <FaragonEngine.h>

#include <imgui/imgui.h>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PlatForm/OpenGL/OpenGLShader.h"

class ExampleLayer : public FaragonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		m_OrthographicCameraController = FaragonEngine::OrthographicCameraController(1280.0f / 720.0f);

		m_VertexArray = FaragonEngine::VertexArray::Create();
		// Add vertex buffer and layout
		FaragonEngine::BufferLayout layout = {
			{ "a_Pos",FaragonEngine::ShaderDataType::Float3},
			{ "a_Color",FaragonEngine::ShaderDataType::Float4},
			{ "a_TexCoord",FaragonEngine::ShaderDataType::Float2}
		};
		float vertices[] = {
			// positions		// colors               // texture coords
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		FaragonEngine::Ref<FaragonEngine::VertexBuffer> vertexBuffer;
		vertexBuffer = FaragonEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Add index buffer
		uint32_t indices[] = { 0, 1, 2 , 2, 3, 0 };
		FaragonEngine::Ref<FaragonEngine::IndexBuffer> indexBuffer;
		indexBuffer = FaragonEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Create Texture
		m_Texture = FaragonEngine::Texture2D::Create("assets/textures/TestTexture.png");

		// Create Shaders
		auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/TextureShader.glsl");
		std::dynamic_pointer_cast<FaragonEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<FaragonEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(FaragonEngine::Timestep deltaTime) override
	{
		m_OrthographicCameraController.OnUpdate(deltaTime);

		FaragonEngine::RenderCommand::SetClearColor(m_ClearColor);
		FaragonEngine::RenderCommand::Clear();

		FaragonEngine::Renderer::BeginScene(m_OrthographicCameraController.GetCamera());

		m_Texture->Bind();

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.0f));

		glm::mat4 transform = translate * rotate * scale;


		FaragonEngine::Renderer::Submit(m_ShaderLibrary.Get("TextureShader"), m_VertexArray, transform);

		FaragonEngine::Renderer::EndScene();
	}

	void OnEvent(FaragonEngine::Event& e) override
	{
		m_OrthographicCameraController.OnEvent(e);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));

		ImGui::End();
	}
private:
	// Renderer
	FaragonEngine::ShaderLibrary m_ShaderLibrary;
	FaragonEngine::Ref<FaragonEngine::Texture2D> m_Texture;
	FaragonEngine::Ref<FaragonEngine::VertexArray> m_VertexArray;
	// Camera
	FaragonEngine::OrthographicCameraController m_OrthographicCameraController;

	//Clear Color
	glm::vec4 m_ClearColor = { 0.2f, 0.3f, 0.6f, 1.0f };
};

class Sandbox : public FaragonEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

};

FaragonEngine::Application* FaragonEngine::CreateApplication()
{
	return new Sandbox();
}



