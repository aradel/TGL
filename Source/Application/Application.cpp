#include "Application.hpp"
#include "../Devices/DeviceFactory.hpp"
#include "../OS/Timer.hpp"
#include "../Devices/Graphics/GraphicsDeviceD3D12.hpp"
#include "../TGL.hpp"

TGL::Application::Application() 
{
	hWnd = 0;

	wndParam.width = 800;
	wndParam.height = 600;
	wndParam.style = TGL::OS::WINDOW_PARAM::Style::DEFAULT;
	wndParam.applicationPtr = this;
}

TGL::Application::~Application() 
{

}

bool TGL::Application::ReadConfig(TGL::ApplicationConfig& config)
{
	//ToDo: Actually read from somewhere.
	bool success = true;

	config.renderDevice = TGL::RendererDeviceType::D3D12;
	config.inputDevice = TGL::InputDeviceType::RawInput;

	gfxSettings.fullscreen = false;
	gfxSettings.screenSize.xWidth = wndParam.width;
	gfxSettings.screenSize.yHeight = wndParam.height;
	gfxSettings.trippleBuffering = false;

	return success;
}

bool TGL::Application::Startup(const TGL::OS::APPLICATION_PARAM& aParam)
{
	if (!ReadConfig(config)) { return false; }

	TGL::OS::WindowCreate(aParam, wndParam, hWnd);

	pInputDevice = DeviceFactory::CreateInputDevice(config.inputDevice);
	pGraphicsDevice = DeviceFactory::CreateGraphicsDevice(config.renderDevice);

	TGL::InputDeviceParameter inputParam;
	inputParam.hWnd = Application::hWnd;
	inputParam.type = InputDeviceParameter::Keyboard;

	TGL::RenderDeviceParameter renderDeviceParam;
	renderDeviceParam.hWnd = Application::hWnd;

	if (!pInputDevice->Initialize(inputParam)) { return false; }
	if (!pGraphicsDevice->Initialize(renderDeviceParam, gfxSettings)) { return false; }

	TGL::RendererParameter rendererParam;
	rendererParam.gfxSettings = gfxSettings;
	rendererParam.pDevice = pGraphicsDevice;

	if (!resourcePool.Initialize(pGraphicsDevice)) { return false; }
	if (!renderer.Initialize(resourcePool, rendererParam)) { return false; }

	return true;
}

void TGL::Application::Shutdown(const TGL::OS::APPLICATION_PARAM& aParam)
{
	resourcePool.Shutdown();
	renderer.Shutdown();

	pInputDevice->Shutdown();
	pGraphicsDevice->Shutdown();

	TGL::OS::WindowDestroy(hWnd, aParam);
}

int TGL::Application::Run(const TGL::OS::APPLICATION_PARAM& aParam)
{
	MSG msg; ZeroMemory(&msg, sizeof(msg));
	if (Application::Startup(aParam))
	{
		Initialize();

		TGL::Timer timer;
		timer.Start();
		while (msg.message != WM_QUIT)
		{
			pInputDevice->Update();
			while ((PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			float fDeltaTime = timer.GetDeltaTime();

			if (!Update(fDeltaTime))
			{
				PostQuitMessage(0x0);
				continue;
			}

			Draw();
			timer.Tick();
		}
	}
	CleanUp();
	Application::Shutdown(aParam);

	return (int)msg.wParam;
}

void TGL::Application::OnInputRecive(WPARAM wParam, LPARAM lParam)
{
	pInputDevice->ReadInput(wParam, lParam);
}

//Application Calls
LRESULT CALLBACK TGL::Application::AppWndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (msg)
	{
		case WM_INPUT: // RawInput - exclusive message
			this->OnInputRecive(wParam, lParam);
			return 0;

		case WM_KEYDOWN: // RawInput - RIDEV_NOLEGACY prevents duplicate MSG
			this->OnInputRecive(wParam, lParam);
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//System Calls
LRESULT CALLBACK TGL::Application::MainWndProc(_In_ HWND hWnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	static TGL::Application* app = nullptr;

	switch (msg)
	{
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0x0);
			return 0;

		case WM_CREATE: // Must be last case in switch
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			app = (TGL::Application*)cs->lpCreateParams;
			return 0;
	}

	return (app != nullptr) ? app->AppWndProc(hWnd, msg, wParam, lParam) : DefWindowProc(hWnd, msg, wParam, lParam);
}
