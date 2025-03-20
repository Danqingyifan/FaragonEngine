#pragma once
#include <string>

namespace FaragonEngine
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}

