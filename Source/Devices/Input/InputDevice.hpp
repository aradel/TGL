#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP
#include "../Interface/IInputDevice.hpp"
namespace TGL
{
	class InputDevice : public TGL::IInputDevice
	{
		private:
			TGL::Input::KeyState cStateDown;
			TGL::Input::KeyState pStateDown;
		public:
			InputDevice();
			virtual ~InputDevice();

			//InputDevice(const InputDevice&) = delete;
			//InputDevice& operator==(const InputDevice&) = delete;
		public:
			bool Initialize(const TGL::InputDeviceParameter& param);
			bool Shutdown(const TGL::InputDeviceParameter& param);
		public:
			void Update();
			void OnInputStateChanged(TGL::Key key, bool state);

			bool IsKeyDown(TGL::Key key) const;
			bool IsKeyUp(TGL::Key key) const;
			bool IsKeyPressed(TGL::Key key) const;
			bool IsKeyReleased(TGL::Key key) const;
		public:
#ifdef TGL_BUILD_WINDOWS
			virtual void ReadInput(WPARAM wParam, LPARAM lParam);
#endif
	};
}
#endif