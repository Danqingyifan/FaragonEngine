#pragma once

#include "FaragonEngine/Core/Core.h"

#include "FaragonEngine/Input/KeyCodes.h"
#include "FaragonEngine/Input/MouseCodes.h"

#include <glm/glm.hpp>

namespace FaragonEngine
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}