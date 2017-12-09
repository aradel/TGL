#include "RawInputDevice.hpp"
#include <vector>
#include <cassert>

TGL::RawInputDevice::RawInputDevice() 
{
	
}

TGL::RawInputDevice::~RawInputDevice()
{

}

bool TGL::RawInputDevice::Initialize(const InputDeviceParameter& param)
{
	bool result_success = false;

	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x0;
	rid[0].dwFlags = RIDEV_NOLEGACY;
	rid[0].hwndTarget = param.hWnd;

	if (param.type == InputDeviceParameter::Mouse) {
		const USHORT RAW_INPUT_MOUSE = 0x02;
		rid[0].usUsage = RAW_INPUT_MOUSE;
		result_success = RegisterRawInputDevices(rid, 1, sizeof(rid[0])) == TRUE;
	}
	if (param.type == InputDeviceParameter::Keyboard)
	{
		const USHORT RAW_INPUT_KEYBOARD = 0x06;
		rid[0].usUsage = RAW_INPUT_KEYBOARD;
		result_success = RegisterRawInputDevices(rid, 1, sizeof(rid[0])) == TRUE;
	}

	return result_success;
}

bool TGL::RawInputDevice::Shutdown(const InputDeviceParameter& param)
{
	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x06;
	rid[0].dwFlags = RIDEV_REMOVE; 
	rid[0].hwndTarget = param.hWnd;

	return RegisterRawInputDevices(rid, 1, sizeof(rid[0])) == TRUE;
}

void TGL::RawInputDevice::ReadInput(WPARAM wParam, LPARAM lParam)
{
	size_t inputSize = 0;
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &inputSize, sizeof(RAWINPUTHEADER));

	if (inputSize > rawBuffer.size())
	{
		rawBuffer.resize(inputSize);
	}

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawBuffer.data(), PUINT(&inputSize), sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)rawBuffer.data();
	if (raw->header.dwType == RIM_TYPEKEYBOARD)
	{
		bool isKeyDown = false;

		if (raw->data.keyboard.Flags == RI_KEY_BREAK)
			isKeyDown = false;
		else if (raw->data.keyboard.Flags == RI_KEY_MAKE)
			isKeyDown = true;

		OnInputStateChanged(TGL::Key(raw->data.keyboard.VKey), isKeyDown);
	}
	else if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		// ToDo
	}

	DefRawInputProc((PRAWINPUT*)rawBuffer.data(), 1, sizeof(RAWINPUTHEADER));
}