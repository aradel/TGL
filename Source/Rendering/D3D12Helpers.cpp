#include "D3D12Helpers.hpp"

D3D12_CPU_DESCRIPTOR_HANDLE TGL::OffsetCpuDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE& handle, INT count, UINT descSize)
{
	handle.ptr += count * descSize;
	return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE TGL::OffsetGpuDescriptor(D3D12_GPU_DESCRIPTOR_HANDLE& handle, INT count, UINT descSize)
{
	handle.ptr += count * descSize;
	return handle;
}