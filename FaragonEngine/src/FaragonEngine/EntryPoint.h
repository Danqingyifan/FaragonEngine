#pragma once

#ifdef FA_PLATFORM_WINDOWS

extern FaragonEngine::Application* FaragonEngine::CreateApplication();

int main(int argc,char** argv)
{
	FaragonEngine::Log::Init();

	FA_CORE_ERROR("�ҵ����罫���ݻ�");
	FA_CLIENT_INFO("MOTHERFUCK");

	auto application = FaragonEngine::CreateApplication();
	application->Run();
	delete application;
}
#endif