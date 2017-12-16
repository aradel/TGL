#ifndef IINPUT_DEVICE_HPP
#define IINPUT_DEVICE_HPP
#include "IDevice.hpp"
#include "../../OS/Defines.hpp"
#include "../../TGL.hpp"
namespace TGL
{
	namespace Input 
	{
		struct KeyState
		{
			bool state[256];
		};

		struct MouseState
		{
			int x;
			int y;
		};
	}

	struct InputDeviceParameter
	{
		enum Type
		{
			Keyboard = 1 << 0,
			Mouse = 1 << 1,
			Controller = 1 << 2,
			Joystick = 1 << 3
		};
		Type type;
		TGL::OS::WindowHandle hWnd;
	};

	class IInputDevice : public TGL::IDevice
	{
		public:
			virtual void Update() = 0;
			virtual void OnInputStateChanged(TGL::Key key, bool state) = 0;

			virtual bool IsKeyDown(TGL::Key key) const = 0;
			virtual bool IsKeyUp(TGL::Key key) const = 0;
			virtual bool IsKeyPressed(TGL::Key key) const = 0;
			virtual bool IsKeyReleased(TGL::Key key) const = 0;
#ifdef TGL_BUILD_WINDOWS
			virtual void ReadInput(WPARAM wParam, LPARAM lParam) = 0;
#endif
	};
}
#endif