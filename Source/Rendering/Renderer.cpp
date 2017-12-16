#include "Renderer.hpp"
#include "../Devices/DeviceFactory.hpp"
#include "../Rendering/Viewport.hpp"

bool TGL::Renderer::Initialize(const TGL::RendererParameter& param)
{
	bool success = false;


	
	return true;
}

void TGL::Renderer::Shutdown()
{

}

void TGL::Renderer::SetViewport(const TGL::Viewport& viewport)
{
	this->viewport = viewport;
}

TGL::Viewport TGL::Renderer::GetViewport()
{
	return viewport;
}

void TGL::Renderer::OnScreenSizeChaged() 
{

}

void TGL::Renderer::OnSettingsChanged(const TGL::GraphicsSettings settings) 
{

}

