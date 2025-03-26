
#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

// Core log macros
#define FA_CORE_CRITICAL(...)	::FaragonEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define FA_CORE_ERROR(...)		::FaragonEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FA_CORE_WARN(...)		::FaragonEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FA_CORE_INFO(...)		::FaragonEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FA_CORE_TRACE(...)		::FaragonEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros									 
#define FA_CRITICAL(...)		::FaragonEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
#define FA_ERROR(...)			::FaragonEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FA_WARN(...)			::FaragonEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FA_INFO(...)			::FaragonEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FA_TRACE(...)			::FaragonEngine::Log::GetClientLogger()->trace(__VA_ARGS__)

namespace FaragonEngine
{
	class FARAGON_API Log
	{
	public:
		Log() = default;
		virtual ~Log() = default;

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_ConsoleSink;
		static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> s_ErrorLogFileSink;
	};
}

