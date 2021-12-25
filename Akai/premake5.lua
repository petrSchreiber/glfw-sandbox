project "Akai"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.hpp",
		"src/**.cpp",
	}

	includedirs
	{
		--"%{wks.location}/Akai/thirdparty/spdlog/include",
		"%{wks.location}/Akai/src",
		"%{IncludeDir.Spdlog}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.Glew}",
		"%{IncludeDir.Glfw}",
	}
	
	libdirs 
	{ 	"%{LibraryDir.VulkanSDK}",
		"%{LibraryDir.Glfw}",
		"%{LibraryDir.Glew}",
		--"Akai/thirdparty/**",
	}

	links
	{
		"opengl32.lib",
		"%{Library.Vulkan}",
		"%{Library.Glew}",
		"%{Library.Glfw}",
		"glu32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

