-- premake5.lua


workspace "Brain"
    architecture "x64"

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
	
	include "Brain/vendor/GLFW"
	include "Brain/vendor/glad"
	include "Brain/vendor/imgui"

project "Brain"
    location "Brain"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "br.pch.h"
	pchsource "Brain/src/br.pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
	}
    
    includedirs
    {
	    "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}
	
	links
	{
	    "GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "BR_PLATFORM_WINDOWS",
            "BR_BUILD_DLL",
            "_WINDLL"
		}

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")  
		}

    filter "configurations:Debug"
        defines
		{
			"BR_DEBUG",
			"BR_ENABLE_ASSERTS"
		}
		buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "BR_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Distribution"
        defines "BR_DIST"
		buildoptions "/MD"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Brain/src"
	}

    links
    {
        "Brain"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "BR_PLATFORM_WINDOWS"
		}

    filter "configurations:Debug"
        defines
		{
			"BR_DEBUG",
			"BR_ENABLE_ASSERTS"
		}
		buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "BR_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Distribution"
        defines "BR_DIST"
		buildoptions "/MD"
        optimize "On"