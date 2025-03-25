#include "FaragonPCH.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace FaragonEngine
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform /*= glm::mat4(1.0f)*/)
	{
		auto openGLShader = std::dynamic_pointer_cast<OpenGLShader>(shader);

		openGLShader->Bind();
		openGLShader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		openGLShader->UploadUniformMat4("u_Transform", transform);

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

}