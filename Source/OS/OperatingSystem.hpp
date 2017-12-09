#ifndef OS_COMMON_HPP
#define OS_COMMON_HPP
#include "Defines.hpp"
namespace TGL
{
	namespace OS 
	{
		void WindowCreate(const TGL::OS::APPLICATION_PARAM& osParam, const TGL::OS::WINDOW_PARAM& wndParam, TGL::OS::WindowHandle& outHWnd);
		void WindowDestroy(TGL::OS::WindowHandle hWnd, const TGL::OS::APPLICATION_PARAM& aParam);
	}

}

#endif 