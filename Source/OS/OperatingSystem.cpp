#include "OperatingSystem.hpp"
#include <Windows.h>
#include <cassert>
//WinMainCRTStartup 
#ifdef TGL_BUILD_WINDOWS

void TGL::OS::WindowCreate(const TGL::OS::APPLICATION_PARAM& aParam, const TGL::OS::WINDOW_PARAM& wndParam, TGL::OS::WindowHandle& outHWnd)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = aParam.wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = aParam.hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = aParam.name;

	RegisterClassExW(&wcex);

	RECT tmp;
	tmp.top = tmp.left = 0;
	tmp.bottom = wndParam.height;
	tmp.right = wndParam.width;

	AdjustWindowRect(&tmp, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(aParam.name, aParam.name, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, wndParam.width, wndParam.height, nullptr, nullptr, aParam.hInstance, wndParam.applicationPtr);

	assert(hWnd != 0x0);
	ShowWindow(hWnd, aParam.nCmdShow);
	UpdateWindow(hWnd);
	SetForegroundWindow(hWnd);

	outHWnd = hWnd;
}

void TGL::OS::WindowDestroy(TGL::OS::WindowHandle hWnd, const TGL::OS::APPLICATION_PARAM& aParam)
{
	::DestroyWindow(hWnd);
	UnregisterClass(aParam.name, aParam.hInstance);
}

#endif