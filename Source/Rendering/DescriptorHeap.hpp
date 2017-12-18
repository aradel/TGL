#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H
#include "../Devices/Render/RenderDevice.hpp"
#include <d3d12.h>
namespace TGL 
{
	struct D3D12Context;

	struct DescriptorHeap
	{
		ID3D12DescriptorHeap* pHeap = nullptr;
		size_t nAllocated = 0;
		size_t stride = 0;
		size_t size = 0;
	};

	//class DescriptorHeapCollection
	//{
	//	enum DescriptorType
	//	{
	//		Resources = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
	//		Samplers = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
	//		RenderTargets = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
	//		DepthStencil = D3D12_DESCRIPTOR_HEAP_TYPE_DSV
	//	};

	//	public:
	//		DescriptorHeap bbDescriptor;
	//		ID3D12DescriptorHeap* pBackBufferHeap = nullptr;

	//	public:
	//		bool Initialize(TGL::D3D12Context& pDevice);
	//		void Shutdown();

	//};
}

#endif