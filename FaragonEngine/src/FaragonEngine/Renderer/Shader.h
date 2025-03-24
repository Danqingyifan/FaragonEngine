#pragma once
#include <string>

namespace FaragonEngine
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filePath);
	};

	class ShaderLibrary
	{
	public:
		ShaderLibrary() = default;
		~ShaderLibrary() = default;

		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Get(const std::string& name);

	private:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		bool Exists(const std::string& name) const;

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}

