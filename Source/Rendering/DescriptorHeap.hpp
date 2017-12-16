#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H
#include "../Devices/Render/RenderDevice.hpp"
#include <d3d12.h>
namespace TGL 
{
	struct D3D12Context;
	class DescriptorHeap 
	{
		private:
			ID3D12DescriptorHeap* pBackBufferHeap = nullptr;
			ID3D12DescriptorHeap* pResourceHeap = nullptr;

			size_t bbSize = 0x0;
		public:
			bool Initialize(TGL::D3D12Context& pDevice);
			void Shutdown();

	};
}

#endif