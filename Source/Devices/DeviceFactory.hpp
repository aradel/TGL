#ifndef DEVICE_FACTORY_HPP
#define DEVICE_FACTORY_HPP


namespace TGL 
{
	struct ApplicationConfig;
	class IInputDevice;
	class IRenderDevice;
	namespace DeviceFactory 
	{
		TGL::IInputDevice* CreateInputDevice(const TGL::ApplicationConfig& param);
		TGL::IRenderDevice* CreateRenderDevice(const TGL::ApplicationConfig& param);
	};
}

#endif