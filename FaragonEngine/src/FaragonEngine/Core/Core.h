#pragma once

#include <memory>

#ifdef FA_PLATFORM_WINDOWS
	#if FA_DYNAMIC_LINK
		#ifdef FA_BUILD_DLL
			#define FARAGON_API __declspec(dllexport)
		#else
			#define FARAGON_API __declspec(dllimport)
		#endif
	#else 
		#define FARAGON_API
	#endif
#else
	#error Faragon Engine only supports Windows
#endif

#ifdef FA_DEBUG
	#if defined(FA_PLATFORM_WINDOWS)
		#define FA_DEBUGBREAK() __debugbreak()
	#elif defined(FA_PLATFORM_LINUX)
		#include <signal.h>
		#define FA_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define FA_ENABLE_ASSERTS
#else
	#define FA_DEBUGBREAK()
#endif

#define FA_EXPAND_MACRO(x) x
#define FA_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define FA_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

namespace FaragonEngine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}	

#include "FaragonEngine/Core/Log.h"
#include "FaragonEngine/Core/Assert.h"
