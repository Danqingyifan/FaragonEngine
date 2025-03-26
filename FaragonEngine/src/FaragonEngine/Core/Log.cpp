#include "FaragonPCH.h"
#include "Log.h"

namespace FaragonEngine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger = 
		std::make_shared<spdlog::logger>("FARAGON_ENGINE");
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger = 
		std::make_shared<spdlog::logger>("APPLICATION");
	std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Log::s_ConsoleSink =
		std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	std::shared_ptr<spdlog::sinks::basic_file_sink_mt> Log::s_ErrorLogFileSink =
		std::make_shared<spdlog::sinks::basic_file_sink_mt>("error.log", true);

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] [%n]: %v%$");
		
		s_ErrorLogFileSink->set_level(spdlog::level::err);
		s_CoreLogger->set_level(spdlog::level::trace);

		s_CoreLogger->sinks().push_back(s_ConsoleSink);
		s_CoreLogger->sinks().push_back(s_ErrorLogFileSink);
		
		s_ClientLogger->sinks().push_back(s_ConsoleSink);
		s_ClientLogger->sinks().push_back(s_ErrorLogFileSink);
	}
}