#pragma once

#include "FaragonEngine/Core/Core.h"

namespace FaragonEngine
{
	class FARAGON_API Input
	{
	public:
		static bool IsKeyPressed(int key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<double, double> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static double GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static double GetMouseY() { return s_Instance->GetMouseYImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(int key) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<double, double> GetMousePositionImpl() = 0;
		virtual double GetMouseXImpl() = 0;
		virtual double GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}