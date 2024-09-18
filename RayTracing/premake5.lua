VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

include "vendor/GLFW"
include "vendor/imgui"

project "RayTracing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "on"

    files
    {
        "src/**.h",
        "src/**.cpp",

		"Sandbox/**.h",
		"Sandbox/**.cpp"
    }

    includedirs
    {
        "src",
		"Sandbox",
        "vendor/glm",
        "vendor/imgui",
		"vendor/stb_image",
        "vendor/glfw/include",

        "%{IncludeDir.VulkanSDK}",
    }

    links
    {
		"ImGui",
		"GLFW",

		"%{Library.Vulkan}",
    }

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines
        { 
            "RT_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "RT_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RT_RELEASE"
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines "RT_DIST"
        runtime "Release"
        optimize "On"
        symbols "Off"