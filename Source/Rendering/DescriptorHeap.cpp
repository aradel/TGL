#include "DescriptorHeap.hpp"
#include "../Devices/Graphics/GraphicsDeviceD3D12.hpp"

#ifdef TGL_BUILD_WINDOWS
namespace Helpers 
{
	D3D12_DESCRIPTOR_HEAP_TYPE ToNativeType(TGL::DescriptorHeapCollection::Type type);
}


bool TGL::DescriptorHeapCollection::Initialize()
{
	// WIP
	ID3D12Device* pDevice; 
	assert(pDevice);

	HRESULT local_result = E_FAIL;
	const size_t nTypes = TGL::DescriptorHeapCollection::TypeCount::Count;

	D3D12_DESCRIPTOR_HEAP_DESC heapDescription[nTypes];
	size_t heapSize[nTypes];

	heapSize[TGL::DescriptorHeapCollection::Type::Resources] = 100;
	heapSize[TGL::DescriptorHeapCollection::Type::Samplers] = 10;
	heapSize[TGL::DescriptorHeapCollection::Type::RenderTargets] = 10;
	heapSize[TGL::DescriptorHeapCollection::Type::DepthStencil] = 10;

	bool success = true;
	for (size_t i = 0; i < nTypes && success; i++) 
	{
		D3D12_DESCRIPTOR_HEAP_TYPE type = Helpers::ToNativeType(TGL::DescriptorHeapCollection::Type(i));

		ZeroMemory(&heapDescription, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
		heapDescription[i].NumDescriptors = heapSize[i];
		heapDescription[i].Type = type;
		heapDescription[i].Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		local_result = pDevice->CreateDescriptorHeap(&heapDescription[i], IID_PPV_ARGS(&descriptorHeap[i].pHeap));
		success = SUCCEEDED(local_result);
	}

	if (!success) 
	{
		Shutdown();
	}
	return success;
}

void TGL::DescriptorHeapCollection::Shutdown()
{
	size_t count = TGL::DescriptorHeapCollection::TypeCount::Count;
	for (size_t i = 0; i < count; i++)
	{
		if (descriptorHeap[i].pHeap) 
		{ 
			descriptorHeap[i].pHeap->Release(); 
			descriptorHeap[i].pHeap = nullptr; 
		}
		descriptorHeap[i].count = 0;
		descriptorHeap[i].size = 0;
		descriptorHeap[i].stride = 0;
	}
}

D3D12_DESCRIPTOR_HEAP_TYPE Helpers::ToNativeType(TGL::DescriptorHeapCollection::Type type)
{
	switch (type)
	{
	case TGL::DescriptorHeapCollection::Type::Resources:
		return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	case TGL::DescriptorHeapCollection::Type::Samplers:
		return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	case TGL::DescriptorHeapCollection::Type::RenderTargets:
		return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	case TGL::DescriptorHeapCollection::Type::DepthStencil:
		return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	default:
		throw 1337;
		break;
	}
}


#endif //TGL_BUILD_WINDOWS