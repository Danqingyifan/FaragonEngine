#include "FaragonPCH.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FaragonEngine
{
	//////////////////////////////////
	///////OrthographicCamera/////////
	//////////////////////////////////

	OrthographicCamera::OrthographicCamera(float aspectRatio, float zoomLevel,bool rotationEnabled)
	{
		m_AspectRatio = aspectRatio;
		m_ZoomLevel = zoomLevel;
		m_RotationEnabled = rotationEnabled;

		float left = -m_AspectRatio * m_ZoomLevel;
		float right = m_AspectRatio * m_ZoomLevel;
		float bottom = -m_ZoomLevel;
		float top = m_ZoomLevel;
		float nearZ = -1.0f;
		float farZ = 1.0f;

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, nearZ, farZ);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	void OrthographicCamera::RecalculateProjectionMatrix(float left, float right, float bottom, float top, float nearZ /*= -1.0f*/, float farZ /*= 1.0f*/)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, nearZ, farZ);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	//////////////////////////////////
	////////PerspectiveCamera/////////
	//////////////////////////////////
}