#pragma once
namespace FaragonEngine
{
	enum class RenderAPI
	{
		None = 0,
		OpenGL = 1,
	};
	class Renderer
	{
	public:
		inline static RenderAPI GetRenderAPI() { return s_RenderAPI; }
	private:
		static RenderAPI s_RenderAPI;
	};
}

