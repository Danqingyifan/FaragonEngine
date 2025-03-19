#pragma once

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
	#define FARAGON_ENABLE_ASSERTS
#endif

#ifdef FARAGON_ENABLE_ASSERTS
	#define FA_ASSERT(x, ...) { if(!(x)) { FA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FA_CORE_ASSERT(x, ...) { if(!(x)) { FA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FA_ASSERT(x, ...)
	#define FA_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FA_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)
