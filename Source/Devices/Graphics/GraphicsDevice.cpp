#include "GraphicsDevice.hpp"
#include "../../TGL.hpp"

void TGL::GraphicsDevice::SetClearColor(float r, float g, float b)
{
	clearColor[0] = TGL::Clamp<float>(0.0f, r, 1.0f);
	clearColor[1] = TGL::Clamp<float>(0.0f, g, 1.0f);
	clearColor[2] = TGL::Clamp<float>(0.0f, b, 1.0f);
	clearColor[3] = 1.0f;
}

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
