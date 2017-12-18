#include "InputDevice.hpp"

TGL::InputDevice::InputDevice()
{
	for (size_t i = 0; i < 256; i++) 
	{
		cStateDown.state[i] = pStateDown.state[i] = false;
	}
}

TGL::InputDevice::~InputDevice() 
{

}

void TGL::InputDevice::Update() 
{
	for (size_t i = 0; i < 256; i++) 
	{
		pStateDown.state[i] = cStateDown.state[i];
		cStateDown.state[i] = false;
	}
}

void TGL::InputDevice::OnInputStateChanged(TGL::Input::Key key, bool state)
{
	cStateDown.state[key] = state;
}

bool TGL::InputDevice::IsKeyDown(TGL::Input::Key key) const
{
	return cStateDown.state[key];
}

bool TGL::InputDevice::IsKeyUp(TGL::Input::Key key) const
{
	return !cStateDown.state[key];
}

bool TGL::InputDevice::IsKeyPressed(TGL::Input::Key key) const
{
	return !pStateDown.state[key] && cStateDown.state[key];
}

bool TGL::InputDevice::IsKeyReleased(TGL::Input::Key key) const
{
	return pStateDown.state[key] && !cStateDown.state[key];
}

void TGL::InputDevice::ReadInput(WPARAM wParam, LPARAM lParam) 
{
	
}