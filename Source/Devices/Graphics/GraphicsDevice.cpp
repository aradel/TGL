#include "GraphicsDevice.hpp"
#include "../../TGL.hpp"

const TGL::DisplayInfo TGL::GraphicsDevice::GetDisplayInfo()
{
	return displayInfo;
}

const TGL::GraphicsCardInfo TGL::GraphicsDevice::GetGraphicsInfo()
{
	return gfxCardInfo;
}

const TGL::RendererDeviceType TGL::GraphicsDevice::GetDeviceType()
{
	return type;
}

