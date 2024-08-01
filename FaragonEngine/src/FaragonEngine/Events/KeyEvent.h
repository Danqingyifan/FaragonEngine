#pragma once

#include "Event.h"

namespace FaragonEngine
{
	class FARAGON_API KeyEvent : public Event
	{
	public:
		// TODO: Add KeyCode enum
		KeyEvent(int key) : m_KeyCode(key) {}

		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}
		int m_KeyCode;
	};
	
	class FARAGON_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key, bool repeat) : KeyEvent(key), m_Repeat(repeat) {}

		inline bool GetIfRepeat() const { return m_Repeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << 
				(m_Repeat? "Repeat" : "Pressed") << ")";

			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)

	private:
		bool m_Repeat;
	};

	class FARAGON_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key) : KeyEvent(key) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;

			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased)
	};

}
