#ifndef GRAPHICS_DEVICE_HPP
#define GRAPHICS_DEVICE_HPP

#include "../Interface/IGraphicsDevice.hpp"
#include "../../Rendering/CommandList.hpp"

#include "../../TGL.hpp"


namespace TGL 
{
#ifdef TGL_BUILD_WINDOWS
	struct DXGIContext;
#endif

	struct SwapChain;
	struct BackBuffer;
	class ResourcePool;

	class GraphicsDevice : public TGL::IRenderDevice
	{
		protected:
			TGL::DisplayInfo displayInfo;
			TGL::GraphicsCardInfo gfxCardInfo;
			TGL::RendererDeviceType type;
		public:
			const TGL::DisplayInfo GetDisplayInfo();
			const TGL::GraphicsCardInfo GetGraphicsInfo();
			const TGL::RendererDeviceType GetDeviceType();
		public:
			virtual bool Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) override = 0;
			virtual void Shutdown() = 0;
			virtual bool CreateSwapChainAndBackBuffer(const TGL::GraphicsSettings& settings, TGL::ResourcePool& resoucePool, TGL::SwapChain& scOut, TGL::BackBuffer& bbOut) = 0;
			virtual bool CreateRenderTarget(TGL::RenderTarget& out) = 0;
			virtual TGL::CommandListPtr CreateCommandList() = 0;
			virtual void ExecuteCommandList(TGL::CommandList* pCmdList) = 0;
			
			virtual void OnScreenSizeChanged(const TGL::ScreenSize& size) = 0;
			virtual void OnSettingsChanged(const TGL::GraphicsSettings& settings) = 0;

			
			//virtual void* GetNativeDevice() = 0;
	};
}

#endif // GRAPHICS_DEVICE_HPP