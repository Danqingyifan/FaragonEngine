#pragma once
#include <FaragonEngine.h>

class Sandbox2D : public FaragonEngine::Layer
{
public:
	Sandbox2D();
	~Sandbox2D();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(FaragonEngine::Timestep deltaTime) override;
	virtual void OnEvent(FaragonEngine::Event& e) override;
	virtual void OnImGuiRender() override;
private:
	// Renderer
	FaragonEngine::ShaderLibrary m_ShaderLibrary;
	FaragonEngine::Ref<FaragonEngine::VertexArray> m_VertexArray;
	// Textures
	FaragonEngine::Ref<FaragonEngine::Texture2D> m_Texture;
	// Camera
	FaragonEngine::OrthographicCameraController m_OrthographicCameraController;
	//Clear Color
	glm::vec4 m_ClearColor = { 0.2f, 0.3f, 0.6f, 1.0f };
};