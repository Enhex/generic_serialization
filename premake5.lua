newoption {
	trigger     = "location",
	value       = "./",
	description = "Where to generate the project.",
}

if not _OPTIONS["location"] then
	_OPTIONS["location"] = "./"
end

--include(_OPTIONS["location"] .. "conandeps.premake5.lua")

workspace("generic_serialization")
	location(_OPTIONS["location"])
	--conan_setup()
	configurations { "Debug", "Release" }

	project("generic_serialization")
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		targetdir(_OPTIONS["location"] .. "bin")

		files{
			"src/**",
			"../shared/src/**"
		}

		includedirs{
			"src",
			"../shared/src"
		}

		--TODO old compilers don't have the option x86-64-v3
		--buildoptions{"-march=x86-64-v3"}

		buildoptions{"-pipe"}
		buildoptions{"-Wall -Wno-missing-braces"}

		filter {"not toolset:clang"}
			linkoptions{"-fuse-ld=gold"}

		filter "toolset:clang"
			buildoptions{"-flto -fwhole-program-vtables -fforce-emit-vtables"}
			linkoptions{'-fuse-ld=lld'}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"

		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"
			linktimeoptimization "On"
			buildoptions{"-fdata-sections -ffunction-sections"} -- needed for -gc-sections
			linkoptions{"-s -Wl,--gc-sections -Wl,--as-needed"}
