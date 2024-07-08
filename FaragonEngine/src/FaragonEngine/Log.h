#pragma once

#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"

namespace FaragonEngine
{
	class FARAGON_API Log
	{
	public:
		Log();
		virtual ~Log();

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define FA_CORE_ERROR(...)	::FaragonEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FA_CORE_WARN(...)	::FaragonEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FA_CORE_INFO(...)	::FaragonEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FA_CORE_TRACE(...)	::FaragonEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros									 
#define FA_Client_ERROR(...)	::FaragonEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FA_Client_WARN(...)		::FaragonEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FA_Client_INFO(...)		::FaragonEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FA_Client_TRACE(...)	::FaragonEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
