#pragma once

#include "FaragonEngine/Input.h"

namespace FaragonEngine
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		~WindowsInput();

		virtual bool IsKeyPressedImpl(int key) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

