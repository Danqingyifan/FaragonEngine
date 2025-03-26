#include "FaragonPCH.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace FaragonEngine
{

	// Class ShaderLibrary
	FaragonEngine::Ref<FaragonEngine::Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		Ref<Shader> shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	FaragonEngine::Ref<FaragonEngine::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		Ref<Shader> shader = Shader::Create(filePath);
		Add(filePath, shader);
		return shader;
	}

	FaragonEngine::Ref<FaragonEngine::Shader> ShaderLibrary::Get(const std::string& name)
	{
		FA_CORE_ASSERT(Exists(name), "{0} Shader not found in library!", name);
		return m_Shaders[name];
	}

	// private
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		FA_CORE_ASSERT(!Exists(name), "Shader name already exists in library!");

		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		FA_CORE_ASSERT(!Exists(name), "Shader name already exists in library!");
		m_Shaders[name] = shader;
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}


	// Class Shader
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		RendererAPI::API api = Renderer::GetRenderAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			FA_CORE_ASSERT(false, "RenderAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);
		default:
			FA_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}