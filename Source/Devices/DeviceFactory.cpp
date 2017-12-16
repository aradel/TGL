#include "DeviceFactory.hpp"
#include "../Application/Settings.hpp"
#ifdef  TGL_BUILD_WINDOWS
#include "../Devices/Input/RawInputDevice.hpp"
#include "../Devices/Render/RenderDeviceD3D12.hpp"
#include "../TGL.hpp"

TGL::InputDevice* TGL::DeviceFactory::CreateInputDevice(TGL::CFG_VAR type)
{
	TGL::InputDevice* local_return = nullptr;

	switch (type)
	{
	case TGL::InputDeviceType::Native:
			local_return = nullptr;
			break;

	case TGL::InputDeviceType::RawInput:
			local_return = new TGL::RawInputDevice();
			break;
	}

	return local_return;
}


TGL::RenderDevice* TGL::DeviceFactory::CreateRenderDevice(TGL::CFG_VAR type)
{
	TGL::RenderDevice* local_return = nullptr;

	switch (type)
	{
		case TGL::RendererDeviceType::D3D11:
			local_return = nullptr;
			break;

		case TGL::RendererDeviceType::D3D12:
			local_return = new TGL::RenderDeviceD3D12();
			break;
		case TGL::RendererDeviceType::OpenGL:
			local_return = nullptr;
			break;
	}

	return local_return;
}

void TGL::DeviceFactory::DestroyDevice(TGL::IDevice* pDevice) 
{
	if (pDevice != nullptr) 
	{
		delete pDevice;
		pDevice = nullptr;
	}
}
#endif //  TGL_BUILD_WINDOWS