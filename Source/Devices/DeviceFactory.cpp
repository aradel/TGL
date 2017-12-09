#include "DeviceFactory.hpp"
#include "../Application/Settings.hpp"
#ifdef  TGL_BUILD_WINDOWS
#include "../Devices/Input/RawInputDevice.hpp"
#include "../Devices/Render/RenderDeviceD3D12.hpp"
TGL::IInputDevice* TGL::DeviceFactory::CreateInputDevice(const TGL::ApplicationConfig& param)
{
	TGL::IInputDevice* local_return = nullptr;

	switch (param.inputDevice)
	{
		case TGL::ApplicationConfig::Input::Native:
			local_return = nullptr;
			break;

		case TGL::ApplicationConfig::Input::RawInput:
			local_return = new TGL::RawInputDevice();
			break;
	}

	return local_return;
}


TGL::IRenderDevice* TGL::DeviceFactory::CreateRenderDevice(const TGL::ApplicationConfig& param)
{
	TGL::IRenderDevice* local_return = nullptr;

	switch (param.renderer)
	{
		case TGL::ApplicationConfig::Renderer::D3D11:
			local_return = nullptr;
			break;

		case TGL::ApplicationConfig::Renderer::D3D12:
			local_return = new TGL::RenderDeviceD3D12();
			break;
		case TGL::ApplicationConfig::Renderer::OpenGL:
			local_return = nullptr;
			break;
	}

	return local_return;
}
#endif //  TGL_BUILD_WINDOWS