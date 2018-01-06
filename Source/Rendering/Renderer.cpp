#include "Renderer.hpp"
#include "../Devices/Graphics/GraphicsDevice.hpp"
#include "../Rendering/Viewport.hpp"
#include "../Rendering/CommandList.hpp"

bool TGL::Renderer::Initialize(TGL::ResourcePool& resourcePool, const TGL::RendererParameter& param)
{
	bool success = false;
	const TGL::GraphicsSettings& gfxSettings = param.gfxSettings;

	param.pDevice->CreateSwapChainAndBackBuffer(gfxSettings, resourcePool, swapChain, backBuffer);
	pCmdList = param.pDevice->CreateCommandList();

	viewport.xTopLeft = 0;
	viewport.yTopLeft = 0;
	viewport.xWidth = uint16(gfxSettings.screenSize.xWidth);
	viewport.yHeight = uint16(gfxSettings.screenSize.yHeight);

	return true;
}

void TGL::Renderer::Shutdown()
{
	swapChain.Release();
	if (pCmdList) { pCmdList->Release();  pCmdList = nullptr; }
}

void TGL::Renderer::SetClearColor(float r, float g, float b)
{
	clearColor[0] = TGL::Clamp<float>(0.0f, r, 1.0f);
	clearColor[1] = TGL::Clamp<float>(0.0f, g, 1.0f);
	clearColor[2] = TGL::Clamp<float>(0.0f, b, 1.0f);
	clearColor[3] = 1.0f;
}

void TGL::Renderer::OnScreenSizeChaged() 
{

}

void TGL::Renderer::OnSettingsChanged(const TGL::GraphicsSettings settings) 
{

}

