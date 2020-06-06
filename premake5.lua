-- premake5.lua

workspace "Brain"
    architecture "x86_64"
	startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--  Include directories relative to the solution directory
	IncludeDir = {}
	IncludeDir["GLFW"] = "Brain/vendor/GLFW/include"
	IncludeDir["glad"] = "Brain/vendor/glad/include"
	IncludeDir["imgui"] = "Brain/vendor/imgui"
	IncludeDir["glm"] = "Brain/vendor/glm"
	IncludeDir["stb_image"] = "Brain/vendor/stb_image"
	
	include "Brain/vendor/GLFW"
	include "Brain/vendor/glad"
	include "Brain/vendor/imgui"
		
project "Brain"
    location "Brain"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "br.pch.h"
	pchsource "Brain/src/br.pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
    
    includedirs
    {
	    "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	
	links
	{
	    "GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

    filter "configurations:Debug"
        defines "BR_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BR_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "BR_DIST"
		runtime "Release"
        optimize "on"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
	}
    
    includedirs
    {
        "Brain/vendor/spdlog/include",
        "Brain/src",
		"Brain/vendor",
		"%{IncludeDir.glm}"
	}

    links
    {
        "Brain"
	}

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

    filter "configurations:Debug"
        defines "BR_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BR_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "BR_DIST"
		runtime "Release"
        optimize "on"
