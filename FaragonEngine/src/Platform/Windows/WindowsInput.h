#pragma once

#include "FaragonEngine/Input/Input.h"

namespace FaragonEngine
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		~WindowsInput();

		virtual bool IsKeyPressedImpl(int key) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<double, double> GetMousePositionImpl() override;
		virtual double GetMouseXImpl() override;
		virtual double GetMouseYImpl() override;
	};
}

