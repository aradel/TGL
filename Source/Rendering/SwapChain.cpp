#include "SwapChain.hpp"

void TGL::SwapChain::Release()
{
	if (pSwapChain) 
	{
		pSwapChain->Release();
		pSwapChain = nullptr;
	}
}