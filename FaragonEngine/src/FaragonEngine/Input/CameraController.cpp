#include "FaragonPCH.h"
#include "CameraController.h"

#include "FaragonEngine/Input/Input.h"
#include "FaragonEngine/Input/KeyCodes.h"

namespace FaragonEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel, bool rotationEnabled)
	{
		m_Camera = OrthographicCamera(aspectRatio, zoomLevel, rotationEnabled);
	}

	void OrthographicCameraController::OnUpdate(float deltaTime)
	{
		// Update Camera Position
		glm::vec3 m_CameraPosition = m_Camera.GetPosition();
		float m_CameraMoveSpeed = m_Camera.GetCameraMoveSpeed();

		if (FaragonEngine::Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		}
		else if (FaragonEngine::Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		}

		if (FaragonEngine::Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		}
		else if (FaragonEngine::Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}

		m_Camera.SetPosition(m_CameraPosition);

		// Update Camera Rotation
		if (m_Camera.IsRotationEnabled())
		{
			float m_CameraRotation = m_Camera.GetRotation();
			float m_CameraRotationSpeed = m_Camera.GetCameraRotationSpeed();

			if (FaragonEngine::Input::IsKeyPressed(Key::Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			}
			else if (FaragonEngine::Input::IsKeyPressed(Key::E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}


	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float zoomLevel = m_Camera.GetZoomLevel();
		zoomLevel -= e.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		m_Camera.SetZoomLevel(zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetAspectRatio(aspectRatio);
		return false;
	}
}
