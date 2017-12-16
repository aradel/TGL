#include "RenderDevice.hpp"
#include "../../TGL.hpp"

void TGL::RenderDevice::SetClearColor(float r, float g, float b)
{
	clearColor[0] = TGL::Clamp<float>(0.0f, r, 1.0f);
	clearColor[1] = TGL::Clamp<float>(0.0f, g, 1.0f);
	clearColor[2] = TGL::Clamp<float>(0.0f, b, 1.0f);
	clearColor[3] = 1.0f;
}

const TGL::DisplayInfo TGL::RenderDevice::GetDisplayInfo() 
{
	return displayInfo;
}

const TGL::GraphicsCardInfo TGL::RenderDevice::GetGraphicsInfo()
{
	return gfxCardInfo;
}

const TGL::RendererDeviceType TGL::RenderDevice::GetDeviceType() 
{
	return type;
}

