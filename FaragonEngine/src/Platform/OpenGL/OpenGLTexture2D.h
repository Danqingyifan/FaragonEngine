#pragma once
#include "FaragonEngine/Renderer/Texture.h"

namespace FaragonEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D() = default;
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D() override;

		void Bind(unsigned int slot = 0) const override;
		void Unbind() const override;

		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}
