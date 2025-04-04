#pragma once
#include "FaragonEngine/Core/Layer.h"

#include "FaragonEngine/Events/KeyEvent.h"
#include "FaragonEngine/Events/MouseEvent.h"
#include "FaragonEngine/Events/WindowEvent.h"

namespace FaragonEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		void Begin();
		void End();

		void OnEvent(Event& e) override;

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		enum ImGuiKey MapKeyToImGuiKey(int keycode,int scancode = 0);
	private:
		float m_Time = 0.0f;

		bool m_BlockEvents = true;
	};
}
