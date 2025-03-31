#include "EditorLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FaragonEngine
{
	EditorLayer::EditorLayer() : Layer("EditorLayer")
	{

	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{
		m_OrthographicCameraController = OrthographicCameraController(1280.0f / 720.0f, 5.0f, false);
		m_Texture = Texture2D::Create("assets/textures/TestTexture2.png");

		m_SpriteSheet = Texture2D::Create("assets/textures/TestSpriteSheet.png");
		m_Tree = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8 };
		m_Framebuffer = Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep deltaTime)
	{
		FA_PROFILE_FUNCTION();

		{
			FA_PROFILE_SCOPE("CameraController::OnUpdate");
			m_OrthographicCameraController.OnUpdate(deltaTime);
		}

		Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		RenderCommand::SetClearColor(m_ClearColor);
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

		{

			FA_PROFILE_SCOPE("Renderer2D::DrawQuad");

			// Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, 0.0f, { 0.5f, 0.5f }, { 0.2f, 0.3f, 0.8f, 1.0f });

			// Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, 0.0f, { 2.0f, 2.0f }, m_Texture, 2.0f, { 0.5f, 0.5f, 0.5f, 1.0f });

			Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, 0.0f, { 1.0f, 2.0f }, m_Tree);
		}

		Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_OrthographicCameraController.OnEvent(e);
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockSpaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Application::Get().Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();


		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));
		ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().DrawCalls);

		ImGui::Image(m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ 1920.0f, 1080.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
	}
}