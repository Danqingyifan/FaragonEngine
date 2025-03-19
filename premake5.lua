-- premake5.lua
workspace "FaragonEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Sandbox"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder(solution directory)
IncludedDir = {}
IncludedDir["GLFW"] = "FaragonEngine/vendor/GLFW/include"
IncludedDir["Glad"] = "FaragonEngine/vendor/Glad/include"
IncludedDir["spdlog"] = "FaragonEngine/vendor/spdlog/include"
IncludedDir["ImGui"] = "FaragonEngine/vendor/imgui"
IncludedDir["glm"] = "FaragonEngine/vendor/glm"

group "Dependencies"
   include "FaragonEngine/vendor/GLFW"
   include "FaragonEngine/vendor/Glad"
   include "FaragonEngine/vendor/imgui"
group ""

project "FaragonEngine"
   location "FaragonEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

   pchheader "FaragonPCH.h"
   pchsource "FaragonEngine/src/FaragonPCH.cpp"

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/glm/**.hpp",
      "%{prj.name}/vendor/glm/**.inl"
   }

   defines
   {
      "_CRT_SECURE_NO_WARNINGS"
   }

   includedirs
   {
      "FaragonEngine/src",
      "%{IncludedDir.GLFW}",
      "%{IncludedDir.Glad}",
      "%{IncludedDir.ImGui}",
      "%{IncludedDir.spdlog}",
      "%{IncludedDir.glm}",
   }

   links
   {
      "GLFW",
      "Glad",
      "ImGui",
      "opengl32.lib"
   }  
   filter "system:windows"
   systemversion "latest"

      defines
      {
         "FA_PLATFORM_WINDOWS",
         "FA_BUILD_DLL",
         "GLFW_INCLUDE_NONE",
      }

   filter "configurations:Debug"
      defines "FA_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "FA_RELEASE"
      runtime "Release"
      optimize "on"

   filter "configurations:Dist"
      defines "FA_DIST"
      runtime "Release"
      optimize "on"


project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   includedirs
   {
      "FaragonEngine/src",
      "FaragonEngine/vendor",
      "%{IncludedDir.spdlog}",
      "%{IncludedDir.glm}",
   }
   
   links
   {
      "FaragonEngine"
   }

   filter "system:windows"

      systemversion "latest"

         defines
         {
            "FA_PLATFORM_WINDOWS"
         }

   filter "configurations:Debug"
      defines "FA_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "FA_RELEASE"
      runtime "Release"
      optimize "on"

   filter "configurations:Dist"
      defines "FA_DIST"
      runtime "Release"
      optimize "on"