#ifndef TGL_H
#define TGL_H
#include "OS/OperatingSystem.hpp"
#include <cassert>
namespace TGL
{

#if _MSC_VER && !__INTEL_COMPILER
	typedef unsigned __int8 int8;
	typedef unsigned __int16 int16;
	typedef unsigned __int32 int32;
	typedef unsigned __int64 int64;
	
	typedef signed __int8 uint8;
	typedef signed __int16 uint16;
	typedef signed __int32 uint32;
	typedef signed __int64 uint64;
#endif
	typedef uint32 TextureHandle;
	typedef size_t CFG_VAR;

	enum InputDeviceType { Native = 0, RawInput = 1 };
	enum RendererDeviceType { D3D11 = 0, D3D12 = 1, OpenGL = 2 };

	struct ApplicationConfig
	{
		CFG_VAR inputDevice;
		CFG_VAR renderDevice;
	};

	//////////////////////////////////
	// Declares Helpers
	//
	template <class T> bool Clamp(T min_, T value_, T max_);
	template <class T> bool InRange(T min_, T value_, T max_);

	//////////////////////////////////
	// Declares Graphics
	//
	struct DisplayInfo;
	struct GraphicsCardInfo;
	struct GraphicsSettings;
	struct ScreenSize;
	//////////////////////////////////
	// Declares Input
	//
	enum Key;

	//////////////////////////////////
	// Defines Helpers
	//
	template <class T> bool InRange(T min_, T value_, T max_)
	{
		return min_ < value_ && value_ < max_;
	}

	template <class T> bool Clamp(T min_, T value_, T max_)
	{
		assert(min_ != max_);

		T local_return = value_ < min_ ? min_ : value_;
		local_return = local_return > max_ ? max_ : local_return;
		return  local_return;
	}


	//////////////////////////////////
	// Defines Graphics
	//

	struct ScreenSize
	{
		size_t xWidth = 0;
		size_t yHeight = 0;
	};

	struct GraphicsSettings
	{
		ScreenSize screenSize;
		bool trippleBuffering;
		bool fullscreen;
	};

	struct DisplayInfo
	{
		const char* name = nullptr;
		size_t refreshNumerator;
		size_t refreshDenominator;
	};

	struct GraphicsCardInfo
	{
		size_t vRam = 0;
		const char* name = nullptr;
	};

	//////////////////////////////////
	// Defines Input

#ifdef TGL_BUILD_WINDOWS
	enum Key
	{
		LeftMouse = VK_LBUTTON,
		RightMouse = VK_RBUTTON,
		Cancel = VK_CANCEL,
		MiddleMouse = VK_MBUTTON,
		X1Mouse = VK_XBUTTON1,
		X2Mouse = VK_XBUTTON2,
		Backspace = VK_BACK,
		Tab = VK_TAB,
		Clear = VK_CLEAR,
		Enter = VK_RETURN,
		Shift = VK_SHIFT,
		Control = VK_CONTROL,
		Alt = VK_MENU,
		Pause = VK_PAUSE,
		CapsLock = VK_CAPITAL,
		IME_KANA = VK_KANA,
		IME_HANGUL = VK_HANGUL,
		IME_JUNJA = VK_JUNJA,
		IME_FINAL = VK_FINAL,
		IME_HANJA = VK_HANJA,
		IME_KANJI = VK_KANJI,
		Escape = VK_ESCAPE,
		IME_CONVERT = VK_CONVERT,
		IME_NONCONVERT = VK_NONCONVERT,
		IME_ACCEPT = VK_ACCEPT,
		IME_MODECHANGE = VK_MODECHANGE,
		Spacebar = VK_SPACE,
		PageUp = VK_PRIOR,
		PageDown = VK_NEXT,
		End = VK_END,
		Home = VK_HOME,
		LeftArrow = VK_LEFT,
		UpArrow = VK_UP,
		RightArrow = VK_RIGHT,
		DownArrow = VK_DOWN,
		Select = VK_SELECT,
		Print = VK_PRINT,
		Execute = VK_EXECUTE,
		PrintScreen = VK_SNAPSHOT,
		Insert = VK_INSERT,
		Delete = VK_DELETE,
		Help = VK_HELP,

		KBD0 = 0x30,
		KBD1 = 0x31,
		KBD2 = 0x32,
		KBD3 = 0x33,
		KBD4 = 0x34,
		KBD5 = 0x35,
		KBD6 = 0x36,
		KBD7 = 0x37,
		KBD8 = 0x38,
		KBD9 = 0x39,

		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,

		LeftWinKey = VK_LWIN,
		RightWinKey = VK_RWIN,
		Sleep = VK_SLEEP,

		Numpad0 = VK_NUMPAD0,
		Numpad1 = VK_NUMPAD1,
		Numpad2 = VK_NUMPAD2,
		Numpad3 = VK_NUMPAD3,
		Numpad4 = VK_NUMPAD4,
		Numpad5 = VK_NUMPAD5,
		Numpad6 = VK_NUMPAD6,
		Numpad7 = VK_NUMPAD7,
		Numpad8 = VK_NUMPAD8,
		Numpad9 = VK_NUMPAD9,
		NumpadMul = VK_MULTIPLY,
		NumpadAdd = VK_ADD,
		Separator = VK_SEPARATOR,
		Subtract = VK_SUBTRACT,
		Decimal = VK_DECIMAL,
		Divide = VK_DIVIDE,

		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		F13 = VK_F13,
		F14 = VK_F14,
		F15 = VK_F15,
		F16 = VK_F16,
		F17 = VK_F17,
		F18 = VK_F18,
		F19 = VK_F19,
		F20 = VK_F20,
		F21 = VK_F21,
		F22 = VK_F22,
		F23 = VK_F23,
		F24 = VK_F24,
	};


#endif
}
#endif