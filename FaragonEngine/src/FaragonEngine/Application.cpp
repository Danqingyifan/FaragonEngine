#include "FaragonPCH.h"

#include "Application.h"
#include "FaragonEngine/Log.h"
#include "FaragonEngine/Events/WindowEvent.h"

#include "FaragonEngine/Input.h"

#include "FaragonEngine/Renderer/Renderer.h"

namespace FaragonEngine
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FA_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		// Add vertex buffer and layout
		BufferLayout layout = {
			{ "a_Pos",ShaderDataType::Float3},
			{ "a_Color",ShaderDataType::Float4}
		};
		float vertices[] = {
			// positions		// colors
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Add index buffer
		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Pos;
			layout (location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Pos, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


		////////////////////////////////////////
		/////////////// Test Code //////////////
		////////////////////////////////////////

		m_SquareVA.reset(VertexArray::Create());
		// Add vertex buffer and layout
		BufferLayout test_layout = {
			{ "a_Pos",ShaderDataType::Float3},
		};
		float test_vertices[] = {
			// positions		
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
		};
		std::shared_ptr<VertexBuffer> test_vertexBuffer;
		test_vertexBuffer.reset(VertexBuffer::Create(test_vertices, sizeof(test_vertices)));
		test_vertexBuffer->SetLayout(test_layout);

		m_SquareVA->AddVertexBuffer(test_vertexBuffer);

		// Add index buffer
		uint32_t test_indices[] = {
			0, 1, 2, // first triangle
			1, 2, 3
		};
		std::shared_ptr<IndexBuffer> test_indexBuffer;
		test_indexBuffer.reset(IndexBuffer::Create(test_indices, sizeof(test_indices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(test_indexBuffer);

		std::string test_vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Pos;

			void main()
			{
				gl_Position = vec4(a_Pos, 1.0);
			}
		)";
		std::string test_fragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.5f, 0.7f, 0.9f, 1.0f);
			}
		)";

		m_SquareShader.reset(new Shader(test_vertexSrc, test_fragmentSrc));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.GetIsHandled())
				break;
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVA);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	Application::~Application()
	{

	}
}
