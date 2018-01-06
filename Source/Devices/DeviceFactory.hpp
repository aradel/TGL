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
		TGL::InputDevicePtr CreateInputDevice(TGL::CFG_VAR type);
		TGL::GraphicsDevicePtr CreateGraphicsDevice(TGL::CFG_VAR type);
	};
}

#endif