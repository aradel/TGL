#ifndef RENDER_TARGET_HPP
#define RENDER_TARGET_HPP
#include <d3d12.h>
namespace TGL 
{
	struct RenderTarget
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		ID3D12Resource* pResource;
	};
}
#endif