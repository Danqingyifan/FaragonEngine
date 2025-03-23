#include "FaragonPCH.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace FaragonEngine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path), m_Width(0), m_Height(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			m_Width = width;
			m_Height = height;

			glCreateTextures(GL_TEXTURE_2D,1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

			glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else
		{
			FA_CORE_ERROR("Failed to load texture: {0}", path);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void OpenGLTexture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
