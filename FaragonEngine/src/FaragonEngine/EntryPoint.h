#pragma once

#ifdef FA_PLATFORM_WINDOWS

extern FaragonEngine::Application* FaragonEngine::CreateApplication();

int main(int argc,char** argv)
{
	FaragonEngine::Log::Init();

	auto application = FaragonEngine::CreateApplication();
	application->Run();
	delete application;
}
#endif