#pragma once
#include "FaragonPCH.h"
#include "FaragonEngine/Events/Event.h"

namespace FaragonEngine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "Faragon Engine", 
					unsigned int width = 1920,
					unsigned int height = 1080)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
		public:
			using EventCallbackFn = std::function<void(Event&)>;

			virtual ~Window() {};

			virtual void OnUpdate() = 0;

			virtual void* GetNativeWindow() const = 0;

			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;

			virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
			virtual void SetVSync(bool enabled) = 0;
			virtual bool IsVSync() const = 0;

			static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}