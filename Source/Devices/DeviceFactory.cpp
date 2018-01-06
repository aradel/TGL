#include "DeviceFactory.hpp"
#include "../Application/Settings.hpp"
#ifdef  TGL_BUILD_WINDOWS
#include "../Devices/Input/RawInputDevice.hpp"
#include "../Devices/Graphics/GraphicsDeviceD3D12.hpp"
#include "../TGL.hpp"

TGL::InputDevicePtr TGL::DeviceFactory::CreateInputDevice(TGL::CFG_VAR type)
{
	TGL::InputDevicePtr local_return = nullptr;

	switch (type)
	{
	case TGL::InputDeviceType::Native:
			local_return = nullptr;
			break;

	case TGL::InputDeviceType::RawInput:
			local_return.reset(new TGL::RawInputDevice());
			break;
	}

	return local_return;
}


TGL::GraphicsDevicePtr TGL::DeviceFactory::CreateGraphicsDevice(TGL::CFG_VAR type)
{
	TGL::GraphicsDevicePtr local_return = nullptr;

	switch (type)
	{
		case TGL::RendererDeviceType::D3D12:
			local_return.reset(new TGL::GraphicsDeviceD3D12());
			break;
		case TGL::RendererDeviceType::Vulcan:
			local_return = nullptr;
			break;
	}

	return local_return;
}

#endif //  TGL_BUILD_WINDOWS