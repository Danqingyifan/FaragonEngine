#include "FaragonPCH.h"
#include "Shader.h"

#include "FaragonEngine/Log.h"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace FaragonEngine
{
	Shader::Shader()
	{

	}

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertexShaderSource = vertexSrc.c_str();
		glShaderSource(vertexShaderID, 1, &vertexShaderSource, 0);

		// Compile vertex shader
		glCompileShader(vertexShaderID);

		// Check for errors
		GLint success = 0;
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShaderID);

			FA_CORE_ERROR("Error compiling vertex shader: {0}", infoLog.data());
			FA_CORE_ASSERT(false, "Error compiling vertex shader");
			return;
		}

		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentShaderSource = fragmentSrc.c_str();
		glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderID);

		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, &infoLog[0]);

			// either of them,don't leak shaders
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			FA_CORE_ERROR("Error compiling fragment shader: {0}", infoLog.data());
			FA_CORE_ASSERT(false, "Error compiling fragment shader");
			return;
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
			glDeleteProgram(program);

			FA_CORE_ERROR("Error linking program: {0}", infoLog.data());
			FA_CORE_ASSERT(false, "Error linking program");
			return;
		}

		// always detach shaders after a successful link
		glDetachShader(program, vertexShaderID);
		glDetachShader(program, fragmentShaderID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}