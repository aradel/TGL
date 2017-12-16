-- Root Directories
local DIR_ROOT = "../"
local DIR_PROJECT = DIR_ROOT .. "Project/"
local DIR_SOURCE = DIR_ROOT .. "Source/"
local DIR_TARGET = DIR_ROOT .. "Binaries/%{cfg.buildcfg}"

-- Module Directories
local DIR_APPLICATION = DIR_SOURCE .. "Application/"
local DIR_DEVICES = DIR_SOURCE .. "Devices/"
local DIR_DEVICES_INTERFACE = DIR_DEVICES .. "Interface/"
local DIR_DEVICES_INPUT = DIR_DEVICES .. "Input/"
local DIR_DEVICES_RENDER = DIR_DEVICES .. "Render/"
local DIR_MATH = DIR_SOURCE .. "Math/"
local DIR_OS = DIR_SOURCE .. "OS/"
local DIR_RENDERING = DIR_SOURCE .. "Rendering/"
local DIR_UTIL = DIR_SOURCE .. "Utilities/"

-- Game Directories
local DIR_GAME = DIR_SOURCE .. "Game/"

-- PCH Directory
--local PCH_DIR = DIR_ROOT .. "Precompiled/"
--print ("PCH_DIR", PCH_DIR) 

local function PrintPaths()
	print ("")
	print ("Project Paths")
	print ("DIR_ROOT", DIR_ROOT)
	print ("DIR_PROJECT", DIR_PROJECT)
	print ("DIR_SOURCE", DIR_SOURCE)
	print ("DIR_TARGET", DIR_TARGET)

	print ("")
	print ("Module Paths")
	print ("DIR_APPLICATION", DIR_APPLICATION)
	print ("DIR_MATH", DIR_MATH)
	print ("DIR_OS", DIR_OS)
	print ("DIR_RENDERING", DIR_RENDERING)
	
	print ("")
	print ("Devices Paths")
	print ("DIR_DEVICES", DIR_DEVICES)
	print ("DIR_DEVICES_INTERFACE", DIR_DEVICES_INTERFACE)
	print ("DIR_DEVICES_INPUT", DIR_DEVICES_INPUT)
	print ("DIR_DEVICES_RENDER", DIR_DEVICES_RENDER)
	
	print ("")
	print ("DIR_UTIL", DIR_UTIL)
	print ("GAME_PATHS")
	print ("DIR_GAME", DIR_GAME)
	print ("")
end

function os.winSdkVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

local function SetupProject()

	workspace("TGL Project")
		location(DIR_PROJECT)	
   		configurations { "Debug","Release" }
		platforms { "Win32", "Win64" }

		filter { "platforms:Win32" }
    			system "Windows"
    			architecture "x86"
			defines {"TGL_BUILD_WINDOWS"}

		filter { "platforms:Win64" }
    			system "Windows"
    			architecture "x86_64"
			defines {"TGL_BUILD_WINDOWS"}

	project "TGL Project"
		kind "WindowedApp"
		entrypoint "WinMainCRTStartup"
		language "C++"
		location(DIR_PROJECT)
		targetdir(DIR_TARGET)
		links { "d3d12", "dxgi" }
		--includedirs { PCH_DIR }
		--pchheader "pch.hpp"
		--pchsource = "pch.cpp" 

		files 	{ 
				DIR_SOURCE .. "**.h", 
				DIR_SOURCE .. "**.c", 
				DIR_SOURCE .. "**.hpp", 
				DIR_SOURCE .. "**.cpp"
			}

		vpaths 	{ 
				["Main"] 					= { DIR_SOURCE .. "Main.cpp" }, 
				["Core"]					= { DIR_SOURCE .. "TGL.hpp", DIR_SOURCE .. "TGL.cpp" },
				["Core/Appplication"]		= { DIR_APPLICATION .. "*.hpp", DIR_APPLICATION .. "*.cpp" },
				["Core/Devices"]			= { DIR_DEVICES .. "*.hpp", DIR_DEVICES .. "*.cpp" },
				["Core/Devices/Interface"]	= { DIR_DEVICES_INTERFACE .. "*.hpp"},
				["Core/Devices/Input"]		= { DIR_DEVICES_INPUT .. "*.hpp", DIR_DEVICES_INPUT .. "*.cpp" },
				["Core/Devices/Render"]		= { DIR_DEVICES_RENDER .. "*.hpp", DIR_DEVICES_RENDER .. "*.cpp" },
				["Core/Math"] 				= { DIR_MATH .. "*.hpp", DIR_MATH .. "*.cpp" },
				["Core/OS"] 				= { DIR_OS .. "*.hpp", DIR_OS .. "*.cpp" },
				["Core/Rendering"]	 		= { DIR_RENDERING .. "*.hpp", DIR_RENDERING .. "*.cpp" },
				["Core/Utilities"] 			= { DIR_UTIL .. "*.hpp", DIR_UTIL .. "*.cpp" },
				["Game"]				= { DIR_GAME .. "*.hpp", DIR_GAME .. "*.cpp" }
				--["Precompiled"]			= { PCH_DIR .. "*.hpp"}
			}

  		filter "configurations:Debug"
	      		defines { "DEBUG" }
	      		symbols "On"

   		filter "configurations:Release"
      			defines { "NDEBUG" }
      			optimize "On"

		filter {"system:windows", "action:vs*"}
    			systemversion(os.winSdkVersion() .. ".0")
end

local function GenerateSolution()
	PrintPaths();
	SetupProject();
end

GenerateSolution();

