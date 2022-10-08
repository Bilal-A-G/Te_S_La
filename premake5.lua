workspace "Te_S_La"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
gameName = "Game"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")
    libdirs("%{prj.name}/lib")
    includedirs("%{prj.name}/include")


    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl"
    }

    links
    {
        "glfw3_mt",
        "glfw3",
        "OpenGL32",
        "assimp-vc142-mt"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "TS_WIN",
            "TS_ENGINE"
        }

        postbuildcommands
        {
            ("{COPY} ../external/assimp" .. " ../bin/" .. outputdir .. "/%{prj.name}"),
            ("{Copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/" .. gameName),
            ("{COPY} ../external/assimp" .. " ../bin/" .. outputdir .. "/" .. gameName)
        }

    filter "configurations:Debug"
        defines "TS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        optimize "On"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    includedirs
    {
        "Engine/src"
    }


    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "TS_WIN"
        }

    filter "configurations:Debug"
        defines "TS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TS_RELEASE"
        optimize "On"