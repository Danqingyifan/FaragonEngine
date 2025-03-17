#pragma once

#include "FaragonEngine/Core.h"

namespace FaragonEngine
{
	class FARAGON_API Input
	{
	public:
		static bool IsKeyPressed(int key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(int key) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}