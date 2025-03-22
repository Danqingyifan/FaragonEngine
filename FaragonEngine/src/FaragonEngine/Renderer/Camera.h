#pragma once

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera() = default;
		OrthographicCamera(float left, float right, float bottom, float top, float nearZ = -1.0f, float farZ = 1.0f);
		~OrthographicCamera() = default;
		
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix( );
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_Rotation = 0.0f;
	};

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fov, float aspectRatio, float nearZ, float farZ);
		~PerspectiveCamera() = default;
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}
