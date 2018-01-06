#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H
#include <d3d12.h>
namespace TGL 
{
	struct D3D12Context;
	struct DescriptorHeap
	{
		ID3D12DescriptorHeap* pHeap = nullptr;
		size_t count = 0;
		size_t size = 0;
		size_t stride = 0;
	};

	class DescriptorHeapCollection
	{
		public:
			enum Type
			{
				Resources = 0,
				Samplers = 1,
				RenderTargets = 2,
				DepthStencil = 3,
			};

			enum TypeCount { Count = 4 };

		public:
			DescriptorHeap descriptorHeap[TypeCount::Count];
		public:
			bool Initialize();
			void Shutdown();

	};
}

#endif