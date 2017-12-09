#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include "../OS/OperatingSystem.hpp"
#include "../Devices/Input/RawInputDevice.hpp"
namespace TGL 
{
	struct ApplicationConfig
	{ 
		typedef size_t CFG_VAR;

		enum Input		{ Native = 0, RawInput = 1 };
		enum Renderer	{ D3D11 = 0, D3D12 = 1, OpenGL = 2 };

		CFG_VAR inputDevice;
		CFG_VAR renderer;
	};

}
#endif