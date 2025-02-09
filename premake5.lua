-- premake5.lua
workspace "FaragonEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder(solution directory)
IncludedDir = {}
IncludedDir["GLFW"] = "FaragonEngine/vendor/GLFW/include"
IncludedDir["Glad"] = "FaragonEngine/vendor/Glad/include"

include "FaragonEngine/vendor/GLFW"
include "FaragonEngine/vendor/Glad"

project "FaragonEngine"
   location "FaragonEngine"
   kind "SharedLib"
   language "C++"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "FaragonPCH.h"
    pchsource "FaragonEngine/src/FaragonPCH.cpp"

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   includedirs
   {
      "FaragonEngine/src",
      "%{prj.name}/vendor/spdlog/include",
      "%{IncludedDir.GLFW}",
      "%{IncludedDir.Glad}"
   }

   links
   {
       "GLFW",
       "Glad",
       "opengl32.lib"
   }  
   filter "system:windows"
   cppdialect "C++20"
   staticruntime "On"
   systemversion "latest"

      defines
      {
         "FA_PLATFORM_WINDOWS",
         "FA_BUILD_DLL",
         "GLFW_INCLUDE_NONE"
      }

      postbuildcommands
      {
         ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
      }

   filter "configurations:Debug"
      defines "FA_DEBUG"
      buildoptions "/MDd"
      symbols "On"

   filter "configurations:Release"
      defines "FA_RELEASE"
      buildoptions "/MD"
      optimize "On"

   filter "configurations:Dist"
      defines "FA_DIST"
      buildoptions "/MD"
      optimize "On"


project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"

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
      "FaragonEngine/vendor/spdlog/include"
   }
   
   links
   {
      "FaragonEngine"
   }

   filter "system:windows"
      cppdialect "C++20"
      staticruntime "On"
      systemversion "latest"

         defines
         {
            "FA_PLATFORM_WINDOWS"
         }

   filter "configurations:Debug"
      defines "FA_DEBUG"
      symbols "On"

   filter "configurations:Release"
      defines "FA_RELEASE"
      optimize "On"

   filter "configurations:Dist"
      defines "FA_DIST"
      optimize "On"