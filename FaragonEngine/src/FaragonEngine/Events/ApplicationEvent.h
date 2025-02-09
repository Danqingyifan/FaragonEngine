
#pragma once

#include "Event.h"

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