#pragma once
#include <FaragonEngine.h>

namespace FaragonEngine 
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep deltaTime) override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;
	private:
		// Renderer
		ShaderLibrary m_ShaderLibrary;
		Ref<VertexArray> m_VertexArray;
		// Textures
		Ref<Texture2D> m_Texture;

		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_Tree;

		//FrameBuffer
		Ref<Framebuffer> m_Framebuffer;

		// Camera
		OrthographicCameraController m_OrthographicCameraController;
		//Clear Color
		glm::vec4 m_ClearColor = { 0.2f, 0.3f, 0.6f, 1.0f };
	};
}