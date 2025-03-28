#pragma once
#include "FaragonEngine/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace FaragonEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader() = default;
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetBool(const std::string& name, bool value) override;
		void SetInt(const std::string& name, int value)  override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value)  override;
		void SetFloat2(const std::string& name, const glm::vec2& vector) override;
		void SetFloat3(const std::string& name, const glm::vec3& vector) override;
		void SetFloat4(const std::string& name, const glm::vec4& vector) override;
		void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		inline virtual const std::string& GetName() const override { return m_Name; }
	private:
		void UploadUniformBool(const std::string& name, bool value);
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}
