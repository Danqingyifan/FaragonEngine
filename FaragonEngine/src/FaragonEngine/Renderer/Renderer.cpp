#include "FaragonPCH.h"
#include "Renderer.h"

namespace FaragonEngine
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}

}