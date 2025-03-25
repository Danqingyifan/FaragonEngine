#pragma once
#include "FaragonEngine/Core/Layer.h"

#include "FaragonEngine/Events/KeyEvent.h"
#include "FaragonEngine/Events/MouseEvent.h"
#include "FaragonEngine/Events/WindowEvent.h"

namespace FaragonEngine
{
	class FARAGON_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

		void OnEvent(Event& event) override;
	private:
		bool  OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool  OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool  OnMouseMovedEvent(MouseMovedEvent& event);
		bool  OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool  OnKeyPressedEvent(KeyPressedEvent& event);
		bool  OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool  OnKeyTypedEvent(KeyTypedEvent& event);
		bool  OnWindowResizeEvent(WindowResizeEvent& event);

		enum ImGuiKey MapKeyToImGuiKey(int keycode,int scancode = 0);
	private:
		float m_Time = 0.0f;
	};
}
