#include "GraphicsDeviceD3D12.hpp"
#include "../../Rendering/PipelineState.hpp"
#include "../../Rendering/CommandList.hpp"
#include "../../Rendering/D3D12Helpers.hpp"
#include "../../TGL.hpp"
#include <dxgi.h>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
#include <comdef.h>
#include <Windows.h>

namespace Helpers 
{
	// D3D Setup Helpers
	static bool CreateDXGIFactory(TGL::DXGIContext& dxgi);
	static bool EnumrateAdapters(TGL::DXGIContext& dxgi, TGL::GraphicsCardInfo& info);
	static bool CreateD3DDevice(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d);
	static bool CreateCommandQueue(TGL::D3D12Context& d3d);

	// DXGI SwapChain Helpers
	static bool EnumrateOutputs(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d, TGL::DisplayInfo& display, const TGL::GraphicsSettings& settings);
	static bool CreateSwapChain(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d, const TGL::DisplayInfo& displayInfo, const TGL::GraphicsSettings& settings, const TGL::RenderDeviceParameter& deviceParam);

	// Support Functions
	static bool CheckTearingSupport(TGL::DXGIContext& context);
	static size_t NumberOfBackbuffers(bool trippleBuffering);
	// Error Handling
	static bool SetErrorIfFailed(HRESULT hResult);
	static void ShowErrorMessage(DWORD eMsg);
}

TGL::GraphicsDeviceD3D12::GraphicsDeviceD3D12()
{
	type = TGL::RendererDeviceType::D3D12;
}

TGL::GraphicsDeviceD3D12::~GraphicsDeviceD3D12()
{

}

bool TGL::GraphicsDeviceD3D12::Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) {
#ifdef DEBUG
	dbgCtrl.Initialize();
#endif
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 3;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	bool success = false;
	success = Helpers::CreateDXGIFactory(dxgi);				if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }
	success = Helpers::EnumrateAdapters(dxgi, gfxCardInfo);	if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }
	success = Helpers::CreateD3DDevice(dxgi, d3d);			if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }
	success = Helpers::CreateCommandQueue(d3d);				if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }

	// Temp Code
	HRESULT local_result = d3d.pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&bbHeap.pHeap));
	bbHeap.stride = d3d.pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	bbHeap.nAllocated = rtvHeapDesc.NumDescriptors;
	bbHeap.size = bbHeap.stride * bbHeap.nAllocated;

	success = Helpers::SetErrorIfFailed(local_result);
	if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }


	// Break Out later to separate Function
	success = Helpers::EnumrateOutputs(dxgi, d3d, displayInfo, settings);			
	if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }
	
	success = Helpers::CreateSwapChain(dxgi, d3d, displayInfo, settings, param);	
	if (!success) { goto RENDER_DEVICE_INITIALIZE_EXIT; }

	D3D12_CPU_DESCRIPTOR_HANDLE bbCpuHandle = bbHeap.pHeap->GetCPUDescriptorHandleForHeapStart();
	size_t stride = bbHeap.stride;

	ID3D12Resource* x[4];
	size_t nBuffers = Helpers::NumberOfBackbuffers(settings.trippleBuffering);
	for (size_t i = 0; i < nBuffers; i++)
	{
		dxgi.pSwapChain->GetBuffer(i, IID_PPV_ARGS(&x[i]));
		d3d.pDevice->CreateRenderTargetView(x[i], nullptr, bbCpuHandle);

		bbCpuHandle = TGL::OffsetCpuDescriptor(bbCpuHandle, 1, stride);

		x[i]->Release();
	}

RENDER_DEVICE_INITIALIZE_EXIT:
	if (!success)
	{
		Helpers::ShowErrorMessage(GetLastError());
		Shutdown();
	}
	return success;
}

void TGL::GraphicsDeviceD3D12::Shutdown()
{
	//descriptorCollection.Shutdown();

	bbHeap.pHeap->Release();

	if (dxgi.pFactory)		{ dxgi.pFactory->Release();			dxgi.pFactory = nullptr; }
	if (dxgi.pAdapter)		{ dxgi.pAdapter->Release();			dxgi.pAdapter = nullptr; }
	if (dxgi.pSwapChain)	{ dxgi.pSwapChain->Release();		dxgi.pSwapChain = nullptr; }

	if (d3d.pCmdQueue)		{ d3d.pCmdQueue->Release();			d3d.pCmdQueue = nullptr; }
	if (d3d.pDevice)		{ d3d.pDevice->Release();			d3d.pDevice = nullptr; }

#ifdef DEBUG
	dbgCtrl.Release();
#endif
}

TGL::CommandListPtr TGL::GraphicsDeviceD3D12::CreateCommandList()
{
	bool success = false;

	UINT gpuMask = 0x0; //Don't care about multi GPUs
	HRESULT local_result = E_FAIL;
	D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;

	ID3D12CommandAllocator* pLocalAllocator = nullptr;
	ID3D12GraphicsCommandList* pLocalCmdList = nullptr;
	TGL::CommandListD3D12* pLocalReturn = new TGL::CommandListD3D12();

	success = (pLocalReturn != nullptr);	
	if (!success) { goto RENDER_DEVICE_CREATE_CMD_LIST_EXIT; }

	local_result = d3d.pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&pLocalAllocator));
	success = SUCCEEDED(local_result);		
	if (!success) { goto RENDER_DEVICE_CREATE_CMD_LIST_EXIT; }

	local_result = d3d.pDevice->CreateCommandList(gpuMask, type, pLocalAllocator, nullptr, IID_PPV_ARGS(&pLocalCmdList));
	success = SUCCEEDED(local_result);	
RENDER_DEVICE_CREATE_CMD_LIST_EXIT:
	TGL::CommandListPtr local_return(nullptr);
	if (success)
	{
		pLocalReturn->pCmdAllocator = pLocalAllocator;
		pLocalReturn->pCmdList = pLocalCmdList;
		local_return.reset(pLocalReturn);
	}
	else
	{
		if (pLocalAllocator) { pLocalAllocator->Release(); }
		if (pLocalCmdList) { pLocalCmdList->Release(); }

		delete pLocalReturn;
	}

	return local_return;
}


void TGL::GraphicsDeviceD3D12::ExecuteCommandList(TGL::CommandList* pCmdList)
{
	CommandListD3D12* pList = dynamic_cast<CommandListD3D12*>(pCmdList);
	if (pList) 
	{
		ID3D12CommandList* ppCommandLists[] = { pList->pCmdList };
		d3d.pCmdQueue->ExecuteCommandLists(1, ppCommandLists);
	}	
}


void TGL::GraphicsDeviceD3D12::OnScreenSizeChanged(const TGL::ScreenSize& size)
{

}

void TGL::GraphicsDeviceD3D12::OnSettingsChanged(const TGL::GraphicsSettings& settings)
{

}


////////////////////////////////////////////////////
// D3D Setup Helpers
//

bool Helpers::CreateDXGIFactory(TGL::DXGIContext& dxgi)
{
	DWORD flags = 0x0;
#ifdef DEBUG
	flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	HRESULT local_result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgi.pFactory));

	return Helpers::SetErrorIfFailed(local_result);
}

bool Helpers::EnumrateAdapters(TGL::DXGIContext& dxgi, TGL::GraphicsCardInfo& info)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	IDXGIAdapter1* adapter = nullptr;
	UINT i = 0;
	HRESULT local_result = E_FAIL;
	do {
		local_result = dxgi.pFactory->EnumAdapters1(i, &adapter);
		if (local_result == S_OK)
		{
			DXGI_ADAPTER_DESC adapterDesc;
			ZeroMemory(&adapterDesc, sizeof(DXGI_ADAPTER_DESC));
			adapter->GetDesc(&adapterDesc);

			info.name = converter.to_bytes(adapterDesc.Description).c_str();
			info.vRam = adapterDesc.DedicatedVideoMemory / (1024 * 1024);

			dxgi.pAdapter = adapter;
			i++;
			break;
		}
	} while (local_result != DXGI_ERROR_NOT_FOUND);

	return Helpers::SetErrorIfFailed(local_result);
}

bool Helpers::CreateD3DDevice(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d)
{
	HRESULT local_result = D3D12CreateDevice(dxgi.pAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&d3d.pDevice));
	return Helpers::SetErrorIfFailed(local_result);
}

bool Helpers::CreateCommandQueue(TGL::D3D12Context& d3d)
{
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc;
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	cmdQueueDesc.NodeMask = 0x0; // GPU Node Mask
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;

	HRESULT local_result = d3d.pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&d3d.pCmdQueue));

	return Helpers::SetErrorIfFailed(local_result);
}


////////////////////////////////////////////////////
// DXGI SwapChain Helpers
//

bool Helpers::EnumrateOutputs(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d, TGL::DisplayInfo& display, const TGL::GraphicsSettings& settings)
{
	// This functions is stupid, and will remain stupid until there is a need to properly enumrate all outputs.
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	IDXGIOutput* pOutput = nullptr;

	size_t nModes = 0;
	size_t i = 0;

	//For Each Monitor
	HRESULT local_result = E_FAIL;
	bool success = false;
	while (dxgi.pAdapter->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC outputDesc;	ZeroMemory(&outputDesc, sizeof(DXGI_OUTPUT_DESC));
		DXGI_MODE_DESC modeToMatch;		ZeroMemory(&modeToMatch, sizeof(DXGI_MODE_DESC));
		DXGI_MODE_DESC modeFound;		ZeroMemory(&modeFound, sizeof(DXGI_MODE_DESC));

		modeToMatch.Format = dxgi.bbPixelFormat;
		modeToMatch.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		modeToMatch.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		modeToMatch.Width = settings.screenSize.xWidth;
		modeToMatch.Height = settings.screenSize.yHeight;

		local_result = pOutput->GetDesc(&outputDesc);
		if (FAILED(local_result)) { break; }
		display.name = converter.to_bytes(outputDesc.DeviceName).c_str();

		local_result = pOutput->FindClosestMatchingMode(&modeToMatch, &modeFound, d3d.pDevice);
		if (FAILED(local_result)) { break; }
		display.refreshDenominator = modeFound.RefreshRate.Denominator;
		display.refreshNumerator = modeFound.RefreshRate.Numerator;
		break;
	}

	pOutput->Release();

	return Helpers::SetErrorIfFailed(local_result);
}

bool Helpers::CreateSwapChain(TGL::DXGIContext& dxgi, TGL::D3D12Context& d3d, const TGL::DisplayInfo& displayInfo, const TGL::GraphicsSettings& settings, const TGL::RenderDeviceParameter& deviceParam)
{
	//Create Swap Chain	
	UINT usageFlag = DXGI_USAGE_BACK_BUFFER;// | DXGI_USAGE_RENDER_TARGET_OUTPUT;// | DXGI_USAGE_SHARED | DXGI_USAGE_UNORDERED_ACCESS;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	swapChainDesc.Width = settings.screenSize.xWidth;
	swapChainDesc.Height = settings.screenSize.yHeight;
	swapChainDesc.Format = dxgi.bbPixelFormat;
	swapChainDesc.Stereo = false;
	swapChainDesc.BufferUsage = usageFlag;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0x0;
	swapChainDesc.BufferCount = Helpers::NumberOfBackbuffers(settings.trippleBuffering);
	swapChainDesc.Scaling = dxgi.scaling;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED; //Might need to change later
	swapChainDesc.Flags = 0x0;//Helpers::CheckTearingSupport(dxgi) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

	DXGI_RATIONAL refreshRate;
	refreshRate.Denominator = displayInfo.refreshDenominator;
	refreshRate.Numerator = displayInfo.refreshNumerator;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc;
	swapChainFullscreenDesc.RefreshRate = refreshRate;
	swapChainFullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainFullscreenDesc.Windowed = settings.fullscreen;
	swapChainFullscreenDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

	HRESULT local_result = dxgi.pFactory->CreateSwapChainForHwnd(d3d.pCmdQueue, deviceParam.hWnd, &swapChainDesc, nullptr, nullptr, &dxgi.pSwapChain);

	if (!FAILED(local_result))
	{
		local_result = dxgi.pFactory->MakeWindowAssociation(deviceParam.hWnd, DXGI_MWA_NO_ALT_ENTER);
	}
	return Helpers::SetErrorIfFailed(local_result);
}

////////////////////////////////////////////////////
// Support Functions
//

bool Helpers::CheckTearingSupport(TGL::DXGIContext& dxgi)
{
	BOOL allowTearing = FALSE;
	HRESULT local_result = dxgi.pFactory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
	return SUCCEEDED(local_result) && allowTearing;
}

size_t Helpers::NumberOfBackbuffers(bool trippleBuffering)
{
	return trippleBuffering ? 2 : 3;
}

bool Helpers::SetErrorIfFailed(HRESULT hResult)
{
	bool success = SUCCEEDED(hResult);
	if (!success) { SetLastError(hResult); }
	return success;
}

void Helpers::ShowErrorMessage(DWORD eMsg)
{
	DWORD formatFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD languageID = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(formatFlag, nullptr, eMsg, languageID, (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	MessageBoxA(0x0, messageBuffer, "D3D12 Device Initialize Failed", MB_OK);

	LocalFree(messageBuffer);
}

////////////////////////////////////////////////////
// Debug
//
#ifdef DEBUG
void TGL::GraphicsDeviceD3D12::DebugController::Initialize()
{
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&dbg))))
	{
		dbg->EnableDebugLayer();
	}
}

void TGL::GraphicsDeviceD3D12::DebugController::Release()
{
	dbg->Release();
}

#endif