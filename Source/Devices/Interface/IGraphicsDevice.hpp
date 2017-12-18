#ifndef IGRAPHICS_DEVICE_HPP
#define IGRAPHICS_DEVICE_HPP
#include "IDevice.hpp"
#include "../../TGL.hpp"
namespace TGL 
{
	struct GraphicsSettings;
	struct RenderDeviceParameter
	{
		TGL::OS::WindowHandle hWnd;
	};

	class IRenderDevice : public TGL::IDevice {
		public:
			virtual bool Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) = 0;
			virtual void Shutdown() = 0;

			virtual void OnScreenSizeChanged(const TGL::ScreenSize& size) = 0;
			virtual void OnSettingsChanged(const TGL::GraphicsSettings& settings) = 0;
	};
}

#endif // IGRAPHICS_DEVICE_HPP