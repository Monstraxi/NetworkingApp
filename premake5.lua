workspace "NetworkApp"
	architecture "x64"
	configurations { "Debug", "Release" }

	project "NetworkApp"
		location "NetworkApp"

		kind "ConsoleApp"
		language "C++"

		files { "**.h", "**.cpp" }

		links { "ws2_32.lib" }

		targetdir ("bin/" .. "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" .. "/%{prj.name}")
		objdir ("bin-int/" .. "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" .. "/%{prj.name}")

		filter "configurations:Debug"
			defines "DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "RELEASE"
			optimize "On"