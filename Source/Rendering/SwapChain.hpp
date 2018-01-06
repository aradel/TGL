#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP
#include <dxgi1_6.h>

namespace TGL 
{
	struct SwapChain
	{
		IDXGISwapChain1* pSwapChain = nullptr;
		size_t nBuffers = 0;
		void Release();
	};
}
#endif // SWAPCHAIN_HPP