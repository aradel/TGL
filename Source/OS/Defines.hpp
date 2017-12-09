#ifndef OS_DEFINES_HPP
#define OS_DEFINES_HPP
// Forward Declare available structs to identify missing ones at compile time.
namespace TGL
{
	namespace OS
	{
		struct APPLICATION_PARAM;
		struct WINDOW_PARAM;
	}
}
#ifdef TGL_BUILD_WINDOWS
#include <Windows.h>
namespace TGL
{
	namespace OS
	{
		typedef HWND WindowHandle;

		struct APPLICATION_PARAM
		{
			HINSTANCE hInstance;
			HINSTANCE hPrevInstance;
			PSTR lpCmdLine;
			INT nCmdShow;
			WNDPROC wndProc;
			LPCWSTR name;
		};

		struct WINDOW_PARAM
		{
			enum Style
			{
				DEFAULT,
				BORDERLESS
			};
			int width;
			int height;
			int style;
			void* applicationPtr;
		};
	}
}
#endif 
#endif