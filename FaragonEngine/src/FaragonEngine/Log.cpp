#include "FaragonPCH.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
namespace FaragonEngine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	Log::Log()
	{

	}
	
	Log::~Log()
	{

	}

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("FARAGON_ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}