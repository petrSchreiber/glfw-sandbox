include "Dependencies.lua"

workspace "AkaiEngine"
	architecture "x86_64"
	startproject "Akai"

	configurations
	{
		"Debug",
		"Release",
	}

	filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--group "Dependencies"
	--include "Akai/thirdparty/glew-2.2.0"
	--include "Akai/thirdparty/glfw-3.3.3.bin.WIN64"
	--include "Akai/thirdparty/spdlog"
group ""

include "Akai"
