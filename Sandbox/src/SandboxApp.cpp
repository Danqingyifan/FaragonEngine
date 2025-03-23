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
		m_Camera = FaragonEngine::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

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
		m_Texture = FaragonEngine::Texture2D::Create("assets/textures/TestTexture2.png");

		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Pos;
			layout (location = 1) in vec4 a_Color;
			layout (location = 2) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;
			out vec2 v_TexCoord;

			void main()
			{
				gl_Position = u_ViewProjection *  u_Transform * vec4(a_Pos, 1.0);

				v_Color = a_Color;
				v_TexCoord = a_TexCoord;
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec4 v_Color;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader = FaragonEngine::Shader::Create(vertexSrc, fragmentSrc);
		std::dynamic_pointer_cast<FaragonEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<FaragonEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(FaragonEngine::Timestep deltaTime) override
	{
		if (FaragonEngine::Input::IsKeyPressed(FA_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		}
		else if (FaragonEngine::Input::IsKeyPressed(FA_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		}

		if (FaragonEngine::Input::IsKeyPressed(FA_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		}
		else if (FaragonEngine::Input::IsKeyPressed(FA_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}

		if (FaragonEngine::Input::IsKeyPressed(FA_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		}
		else if (FaragonEngine::Input::IsKeyPressed(FA_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
		}

		FaragonEngine::RenderCommand::SetClearColor(m_ClearColor);
		FaragonEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		FaragonEngine::Renderer::BeginScene(m_Camera);

		m_Texture->Bind();

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.0f));

		glm::mat4 transform = translate * rotate * scale;

		FaragonEngine::Renderer::Submit(m_TextureShader, m_VertexArray, transform);

		FaragonEngine::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));

		ImGui::End();
	}
private:
	// Renderer
	FaragonEngine::Ref<FaragonEngine::Shader> m_FlatColorShader;
	FaragonEngine::Ref<FaragonEngine::Shader> m_TextureShader;
	FaragonEngine::Ref<FaragonEngine::Texture2D> m_Texture;
	FaragonEngine::Ref<FaragonEngine::VertexArray> m_VertexArray;

	// Camera
	FaragonEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 36.0f;

	//Clear Color
	glm::vec4 m_ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
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



