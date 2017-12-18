#ifndef DEVICE_FACTORY_HPP
#define DEVICE_FACTORY_HPP
#include "../TGL.hpp"

namespace TGL 
{
	struct ApplicationConfig;
	class IDevice;
	class InputDevice;
	class GraphicsDevice;
	namespace DeviceFactory 
	{
		TGL::InputDevice* CreateInputDevice(TGL::CFG_VAR type);
		TGL::GraphicsDevice* CreateGraphicsDevice(TGL::CFG_VAR type);

		void DestroyDevice(TGL::IDevice* pDevice);
	};
}

#endif