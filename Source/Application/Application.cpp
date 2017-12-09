#include "Application.hpp"
#include "../Devices/DeviceFactory.hpp"
#include "../OS/Timer.hpp"

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
	delete inputDevice;
	delete renderDevice;
}

bool TGL::Application::ReadConfig(TGL::ApplicationConfig& config)
{
	//ToDo: Actually read from somewhere.
	bool success = true;

	config.renderer = TGL::ApplicationConfig::D3D11;
	config.inputDevice = TGL::ApplicationConfig::RawInput;

	return success;
}

bool TGL::Application::Startup(const TGL::OS::APPLICATION_PARAM& aParam)
{
	bool success = ReadConfig(config);
	if(success)
	{
		TGL::OS::WindowCreate(aParam, wndParam, hWnd);
		
		inputDevice = DeviceFactory::CreateInputDevice(config);

		inputParam.hWnd = Application::hWnd;
		inputParam.type = InputDeviceParameter::Keyboard;

		inputDevice->Initialize(inputParam);
	}
	return success;
}

void TGL::Application::Shutdown(const TGL::OS::APPLICATION_PARAM& aParam)
{
	inputDevice->Shutdown(inputParam);

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
			inputDevice->Update();
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
	inputDevice->ReadInput(wParam, lParam);
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
