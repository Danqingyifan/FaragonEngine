#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D")
{

}

Sandbox2D::~Sandbox2D()
{

}

void Sandbox2D::OnAttach()
{
	m_OrthographicCameraController = FaragonEngine::OrthographicCameraController(1280.0f / 720.0f);
	m_Texture = FaragonEngine::Texture2D::Create("assets/textures/TestTexture2.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(FaragonEngine::Timestep deltaTime)
{
	FA_PROFILE_FUNCTION();

	{
		FA_PROFILE_SCOPE("CameraController::OnUpdate");
		m_OrthographicCameraController.OnUpdate(deltaTime);
	}

	FaragonEngine::RenderCommand::SetClearColor(m_ClearColor);
	FaragonEngine::RenderCommand::Clear();

	FaragonEngine::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	{
		FA_PROFILE_SCOPE("Renderer2D::DrawQuad");

		FaragonEngine::Renderer2D::DrawQuad();
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.3f });
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, 45.0f);
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 0.0f, { 0.75f, 0.75f });
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, 0.0f, { 0.5f, 0.5f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, 0.0f, { 1.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f }, m_Texture);
		FaragonEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, 0.0f, { 2.0f, 2.0f }, { 0.5f, 0.5f, 0.5f, 1.0f }, m_Texture, 2.0f);
	}

	FaragonEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(FaragonEngine::Event& e)
{
	m_OrthographicCameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));

	ImGui::End();
}
