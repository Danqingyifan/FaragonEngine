#pragma once

#ifdef FA_PLATFORM_WINDOWS

extern FaragonEngine::Application* FaragonEngine::CreateApplication();

int main(int argc, char** argv)
{
	FaragonEngine::Log::Init();

	FA_PROFILE_BEGIN_SESSION("Startup", "FaragonEngineProfile-Startup.json");
	auto application = FaragonEngine::CreateApplication();
	FA_PROFILE_END_SESSION();

	FA_PROFILE_BEGIN_SESSION("Runtime", "FaragonEngineProfile-Runtime.json");
	application->Run();
	FA_PROFILE_END_SESSION();

	FA_PROFILE_BEGIN_SESSION("Shutdown", "FaragonEngineProfile-Shutdown.json");
	delete application;
	FA_PROFILE_END_SESSION();
}
#endif