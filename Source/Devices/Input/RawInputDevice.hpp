#ifndef RAW_INPUT_DEVICE_HPP
#define RAW_INPUT_DEVICE_HPP
#ifdef TGL_BUILD_WINDOWS
#include "InputDevice.hpp"
#include <vector>

namespace TGL
{
	class RawInputDevice final : public InputDevice 
	{
		private:
			std::vector<BYTE> rawBuffer;
			std::vector<RAWINPUTDEVICE> registeredDevices;
		public:
			RawInputDevice();
			virtual ~RawInputDevice();
		public:
			void ReadInput(WPARAM wParam, LPARAM lParam);
		public:
			virtual bool Initialize(const TGL::InputDeviceParameter& param);
			virtual bool Shutdown();

	};
}
#endif // TGL_BUILD_WINDOWS
#endif // RAW_INPUT_DEVICE_HPP