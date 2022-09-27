workspace "Project-Scientia"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Project Scientia"
    location "Project Scientia"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir)
    objdir ("int/" .. outputdir)
    libdirs("%{prj.name}/lib")
    includedirs("%{prj.name}/include")


    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    links
    {
        "glfw3_mt",
        "glfw3",
        "OpenGL32"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PS_WIN"
        }

    filter "configurations:Debug"
        defines "PS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "PS_RELEASE"
        optimize "On"
