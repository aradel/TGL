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
			virtual bool Initialize(const TGL::InputDeviceParameter& param) = 0;
			virtual bool Shutdown() = 0;
		public:
			void Update();
			void OnInputStateChanged(TGL::Input::Key key, bool state);

			bool IsKeyDown(TGL::Input::Key key) const;
			bool IsKeyUp(TGL::Input::Key key) const;
			bool IsKeyPressed(TGL::Input::Key key) const;
			bool IsKeyReleased(TGL::Input::Key key) const;
		public:
#ifdef TGL_BUILD_WINDOWS
			virtual void ReadInput(WPARAM wParam, LPARAM lParam);
#endif
	};
}
#endif