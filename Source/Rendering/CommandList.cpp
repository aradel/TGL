#include "CommandList.hpp"
#include "../Rendering/Viewport.hpp"
#include <cassert>
#define VALIDATE_STATE assert(state == State::NotRecording);

void TGL::CommandListD3D12::Release() 
{
	if (pCmdAllocator)	{ pCmdAllocator->Release();		pCmdAllocator = nullptr; }
	if (pCmdList)		{ pCmdList->Release();			pCmdList = nullptr; }
}	

void TGL::CommandListD3D12::StartRecording() 
{
	assert(state == State::NotRecording);
	if (InterlockedIncrementAcquire(&state) != 0) 
	{
		HRESULT local_result = E_FAIL;

		local_result = pCmdAllocator->Reset();
		if (!SUCCEEDED(local_result)) { throw local_result; }

		local_result = pCmdList->Reset(pCmdAllocator, nullptr);
		if (!SUCCEEDED(local_result)) { throw local_result; }
	}
}

void TGL::CommandListD3D12::StopRecording() 
{
	assert(state == State::Recording);
	HRESULT local_result = pCmdList->Close();
	if (!SUCCEEDED(local_result)) { throw local_result; }

	if (InterlockedDecrementAcquire(&state) == 0) 
	{
		throw 0x1337;
	}

	assert(state == State::NotRecording);
}

void TGL::CommandListD3D12::ClearRenderTarget(uint8 r, uint8 g, uint8 b) 
{
	VALIDATE_STATE;

	float clearColor[4];
	clearColor[0] = float(r / 255);
	clearColor[1] = float(g / 255);
	clearColor[2] = float(b / 255);
	clearColor[3] = 1.0f;
	//pCmdList->ClearRenderTargetView();

	//Not Implemented
}

void TGL::CommandListD3D12::SetViewPort(const TGL::ViewPort& viewPort) 
{
	VALIDATE_STATE;
	D3D12_VIEWPORT vp;
	vp.TopLeftX = viewPort.xTopLeft;
	vp.TopLeftY = viewPort.yTopLeft;
	vp.Width = viewPort.xWidth;
	vp.Height = viewPort.yHeight;

	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;

	pCmdList->RSSetViewports(1, &vp);
}

bool TGL::CommandListD3D12::SetPipelineState(const TGL::PipelineState& pipeline)
{
	VALIDATE_STATE;

	return false; //Not Implemented
}