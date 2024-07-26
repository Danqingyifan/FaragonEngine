
#pragma once

#include "Event.h"

namespace FaragonEngine
{
	class FARAGON_API MouseEvent : public Event
	{
	public:

		MouseEvent(EventType type) : m_Type(type) {}

		EventType GetType() const { return m_Type; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
	protected:
		EventType m_Type;
	};

	class FARAGON_API MouseMovedEvent : public MouseEvent
	{
	public:

		MouseMovedEvent(float x, float y) :MouseEvent(EventType::MouseMoved), m_X(x), m_Y(y) {}

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

		EVENT_CLASS_TYPE(MouseMoved);

	private:
		float m_X, m_Y;
	};

	class FARAGON_API MouseScrolledEvent : public MouseEvent
	{
	public:

		MouseScrolledEvent(float xOffset, float yOffset) :MouseEvent(EventType::MouseScrolled), m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		EVENT_CLASS_TYPE(MouseScrolled);

	private:
		float m_XOffset, m_YOffset;
	};
}