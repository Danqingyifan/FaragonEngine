#include <FaragonEngine.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public FaragonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		m_Camera = FaragonEngine::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		m_VertexArray.reset(FaragonEngine::VertexArray::Create());

		// Add vertex buffer and layout
		FaragonEngine::BufferLayout layout = {
			{ "a_Pos",FaragonEngine::ShaderDataType::Float3},
			{ "a_Color",FaragonEngine::ShaderDataType::Float4}
		};
		float vertices[] = {
			// positions		// colors
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<FaragonEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(FaragonEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Add index buffer
		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<FaragonEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(FaragonEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Pos;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection *  u_Transform * vec4(a_Pos, 1.0);
				v_Color = a_Color;
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Color);
			}
		)";

		m_Shader.reset(new FaragonEngine::Shader(vertexSrc, fragmentSrc));

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

		FaragonEngine::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
		FaragonEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		FaragonEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 1.0f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 1.0f));

		glm::mat4 transform = translate * rotate * scale;
		FaragonEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);

		FaragonEngine::Renderer::EndScene();
	}

private:
	std::shared_ptr<FaragonEngine::Shader> m_Shader;
	std::shared_ptr<FaragonEngine::VertexArray> m_VertexArray;

	// Camera
	FaragonEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 36.0f;
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



