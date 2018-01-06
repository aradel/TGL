#ifndef GRAPHICS_DEVICE_D3D12_HPP
#define GRAPHICS_DEVICE_D3D12_HPP
#include "GraphicsDevice.hpp"
#include <d3d12.h>
#include <dxgi1_6.h>

namespace TGL 
{
	struct DXGIContext 
	{
		IDXGIFactory5* pFactory = nullptr;
		IDXGIAdapter1* pAdapter = nullptr;
	};

	struct D3D12Context 
	{
		ID3D12Device* pDevice = nullptr;
		ID3D12CommandQueue* pCmdQueue = nullptr;
	};

	class GraphicsDeviceD3D12 final : public TGL::GraphicsDevice
	{
		private:
			DXGIContext dxgi;
			D3D12Context d3d;
			TGL::OS::WindowHandle hWnd;
		public:
			GraphicsDeviceD3D12();
			~GraphicsDeviceD3D12();
		public:

		public: // RenderDevice
			bool Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) override;
			void Shutdown() override;

			bool CreateSwapChainAndBackBuffer(const TGL::GraphicsSettings& settings, TGL::ResourcePool& resoucePool, TGL::SwapChain& scOut, TGL::BackBuffer& bbOut);

			bool CreateRenderTarget(TGL::RenderTarget& out);
			TGL::CommandListPtr CreateCommandList() override;
			void ExecuteCommandList(TGL::CommandList* pCmdList) override;

			void OnScreenSizeChanged(const TGL::ScreenSize& size) override;
			void OnSettingsChanged(const TGL::GraphicsSettings& settings) override;
#ifdef DEBUG
		private:
			struct DebugController
			{
				ID3D12Debug* dbg = nullptr;
				void Initialize();
				void Release();
			};
			DebugController dbgCtrl;
#endif
	};
}

#endif // GRAPHICS_DEVICE_D3D12_HPP