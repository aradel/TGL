#include "Renderer.hpp"
#include "../Devices/DeviceFactory.hpp"
#include "../Rendering/Viewport.hpp"
#include "../Rendering/CommandList.hpp"

bool TGL::Renderer::Initialize(const TGL::RendererParameter& param)
{
	bool success = false;
	const TGL::GraphicsSettings& gfxSettings = param.gfxSettings;

	viewport.xTopLeft = 0;
	viewport.yTopLeft = 0;
	viewport.xWidth = uint16(gfxSettings.screenSize.xWidth);
	viewport.yHeight = uint16(gfxSettings.screenSize.yHeight);

	pCmdList = param.pDevice->CreateCommandList();

	return true;
}

void TGL::Renderer::Shutdown()
{
	pCmdList->Release();
}

void TGL::Renderer::OnScreenSizeChaged() 
{

}

void TGL::Renderer::OnSettingsChanged(const TGL::GraphicsSettings settings) 
{

}

