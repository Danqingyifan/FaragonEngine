#pragma once

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera() = default;
		OrthographicCamera(float aspectRatio, float zoomLevel, bool rotationEnabled = false);
		~OrthographicCamera() = default;

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }
		inline float GetCameraMoveSpeed() const { return m_CameraMoveSpeed; }
		inline float GetCameraRotationSpeed() const { return m_CameraRotationSpeed; }
		inline bool IsRotationEnabled() const { return m_RotationEnabled; }
		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline float GetAspectRatio() const { return m_AspectRatio; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		inline void SetCameraMoveSpeed(float speed) { m_CameraMoveSpeed = speed; }
		inline void SetCameraRotationSpeed(float speed) { m_CameraRotationSpeed = speed; }
		inline void SetRotationEnabled(bool enabled) { m_RotationEnabled = enabled; }
		inline void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; RecalculateProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel); }
		inline void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; RecalculateProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel); }
		
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix(float left, float right, float bottom, float top, float nearZ = -1.0f, float farZ = 1.0f);
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_Rotation = 0.0f;
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotationSpeed = 36.0f;

		float m_AspectRatio;
		float m_ZoomLevel;
		bool m_RotationEnabled;
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
