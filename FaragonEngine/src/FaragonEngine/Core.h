#pragma once

#ifdef FA_PLATFORM_WINDOWS
	#ifdef FA_BUILD_DLL
		#define FARAGON_API __declspec(dllexport)
	#else
		#define FARAGON_API __declspec(dllimport)
	#endif
#else 
	#error Faragon Engine only supports Windows
#endif

#define BIT(x) (1 << x)
