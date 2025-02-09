#pragma once
#include "Event.h"

namespace FaragonEngine 
{
	class FARAGON_API WindowEvent : public Event
	{
	public:
		WindowEvent(EventType type)
			: m_Type(type) {}

		inline EventType GetType() const { return m_Type; }

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		EventType m_Type;
	};

	// Window Events
	class FARAGON_API WindowCloseEvent : public WindowEvent
	{
	public:

		WindowCloseEvent()
			: WindowEvent(EventType::WindowClose) {}

		std::string ToString() const override

		{
			return "WindowCloseEvent";
		}

		EVENT_CLASS_TYPE(WindowClose)
	};
	class FARAGON_API WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: WindowEvent(EventType::WindowResize), m_Width(width), m_Height(height) {}

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
	class FARAGON_API WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent()
			: WindowEvent(EventType::WindowFocus) {}

		std::string ToString() const override
		{
			return "WindowFocusEvent";
		}

		EVENT_CLASS_TYPE(WindowFocus)
	};

}