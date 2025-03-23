#pragma once
namespace FaragonEngine
{
	class Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D() = default;
		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(const std::string& path);
	};
}

