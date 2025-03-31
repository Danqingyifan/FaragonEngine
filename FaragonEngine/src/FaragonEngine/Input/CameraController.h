#pragma once
#include "FaragonEngine\Events\Event.h"
#include "FaragonEngine\Events\MouseEvent.h"
#include "FaragonEngine\Events\WindowEvent.h"

#include "FaragonEngine\Renderer\Camera.h"

namespace FaragonEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController() = default;
		OrthographicCameraController(float aspectRatio, float zoomLevel = 1.0f, bool rotationEnabled = false);
		~OrthographicCameraController() = default;

		void OnUpdate(float deltaTime);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		OrthographicCamera m_Camera;
	};

	class PerspectiveCameraController
	{
		PerspectiveCameraController() = default;
		~PerspectiveCameraController() = default;
	};
}