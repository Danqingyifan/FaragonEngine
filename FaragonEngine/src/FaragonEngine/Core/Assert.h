#pragma once
#include "FaragonEngine/Core/Core.h"
#include "FaragonEngine/Core/Log.h"
#include <filesystem>

#ifdef FA_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define FA_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { FA##type##ERROR(msg, __VA_ARGS__); FA_DEBUGBREAK(); } }
	#define FA_INTERNAL_ASSERT_WITH_MSG(type, check, ...) FA_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define FA_INTERNAL_ASSERT_NO_MSG(type, check) FA_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", FA_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename	().string(), __LINE__)
	
	#define FA_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define FA_INTERNAL_ASSERT_GET_MACRO(...) FA_EXPAND_MACRO( FA_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, FA_INTERNAL_ASSERT_WITH_MSG, FA_INTERNAL_ASSERT_NO_MSG) )
	
	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define FA_ASSERT(...) FA_EXPAND_MACRO( FA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define FA_CORE_ASSERT(...) FA_EXPAND_MACRO( FA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define FA_ASSERT(...)
	#define FA_CORE_ASSERT(...)
#endif