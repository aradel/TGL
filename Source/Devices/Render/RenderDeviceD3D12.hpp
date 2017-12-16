#ifndef RENDER_DEVICE_D3D12_HPP
#define RENDER_DEVICE_D3D12_HPP
#include "RenderDevice.hpp"
#include "../Interface/IRenderDevice.hpp"
#include "../../Rendering/DescriptorHeap.hpp"
#include <d3d12.h>
#include <dxgi1_6.h>

namespace TGL 
{
	struct DXGIContext 
	{
		IDXGIFactory5* pFactory = nullptr;
		IDXGIAdapter1* pAdapter = nullptr;
		IDXGISwapChain1* pSwapChain = nullptr;

		DXGI_SCALING scaling = DXGI_SCALING::DXGI_SCALING_NONE;
		DXGI_FORMAT bbPixelFormat = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	};

	struct D3D12Context 
	{
		ID3D12Device* pDevice = nullptr;
		ID3D12CommandQueue* pCmdQueue = nullptr;
		ID3D12CommandAllocator* pCmdAllocator = nullptr;
	};

	class RenderDeviceD3D12 final : public TGL::RenderDevice
	{
		private:
			DXGIContext dxgi;
			D3D12Context d3d;
			TGL::DescriptorHeap descriptorHeap;
		public:
			RenderDeviceD3D12();
			~RenderDeviceD3D12();
		public:

		public: // RenderDevice
			bool Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) override;
			void Shutdown() override;
			
			TGL::CommandList* CreateCommandList() override;


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

#endif // RENDER_DEVICE_D3D12_HPP