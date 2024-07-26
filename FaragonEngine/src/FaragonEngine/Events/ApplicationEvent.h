
#pragma once

#include "Event.h"

#include <sstream>

namespace FaragonEngine
{
	class FARAGON_API ApplicationEvent : public Event
	{
	public:
		ApplicationEvent(EventType type)
			: m_Type(type) {}

		inline EventType GetType() const { return m_Type; }

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		EventType m_Type;
	};
	class FARAGON_API WindowCloseEvent : public ApplicationEvent
	{
	public:

		WindowCloseEvent()
			: ApplicationEvent(EventType::WindowClose) {}

		std::string ToString() const override

		{
			return "WindowCloseEvent";
		}

		EVENT_CLASS_TYPE(WindowClose)
	};
	class FARAGON_API WindowResizeEvent : public ApplicationEvent
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: ApplicationEvent(EventType::WindowResize), m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)

	private:
		unsigned int m_Width, m_Height;
	};
	class FARAGON_API WindowFocusEvent : public ApplicationEvent
	{
	public:
		WindowFocusEvent()
			: ApplicationEvent(EventType::WindowFocus) {}

		std::string ToString() const override
		{
			return "WindowFocusEvent";
		}

		EVENT_CLASS_TYPE(WindowFocus)
	};

	class FARAGON_API AppTickEvent : public ApplicationEvent
	{
	public:
		AppTickEvent()
			: ApplicationEvent(EventType::AppTick) {}

		std::string ToString() const override
		{
			return "AppTickEvent";
		}

		EVENT_CLASS_TYPE(AppTick)
	};

	class FARAGON_API AppUpdateEvent : public ApplicationEvent
	{
	public:
		AppUpdateEvent()
			: ApplicationEvent(EventType::AppUpdate) {}

		std::string ToString() const override
		{
			return "AppUpdateEvent";
		}

		EVENT_CLASS_TYPE(AppUpdate)
	};

	class FARAGON_API AppRenderEvent : public ApplicationEvent
	{
	public:
		AppRenderEvent()
			: ApplicationEvent(EventType::AppRender) {}

		std::string ToString() const override
		{
			return "AppRenderEvent";
		}

		EVENT_CLASS_TYPE(AppRender)
	};
}