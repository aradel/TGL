#include "DescriptorHeap.hpp"
#include "../Devices/Render/RenderDeviceD3D12.hpp"
bool TGL::DescriptorHeap::Initialize(TGL::D3D12Context& d3d)
{
	ID3D12Device* pDevice = d3d.pDevice;
	assert(pDevice);

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 3;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	
	HRESULT local_result = pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pBackBufferHeap));

	bbSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	bool success = SUCCEEDED(local_result);
	if (!success) { SetLastError(local_result); }
	return success;
}

void TGL::DescriptorHeap::Shutdown() 
{
	if (pBackBufferHeap) { pBackBufferHeap->Release();		pBackBufferHeap = nullptr; }
}