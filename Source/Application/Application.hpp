#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#ifdef TGL_BUILD_WINDOWS
#include "Settings.hpp"
#include "../OS/OperatingSystem.hpp"
#include "../Rendering/Renderer.hpp"

namespace TGL 
{
	class GraphicsDevice;
	class InputDevice;
	class Application 
	{
		protected:
			TGL::Renderer renderer;
			TGL::ResourcePool resourcePool;

			TGL::InputDevice* pInputDevice = nullptr;
			TGL::GraphicsDevice* pRenderDevice = nullptr;

			TGL::OS::WindowHandle hWnd;
			TGL::OS::WINDOW_PARAM wndParam;
			TGL::ApplicationConfig config;
			TGL::GraphicsSettings gfxSettings;
		public:
			Application();
			virtual ~Application();
		private:
			bool ReadConfig(TGL::ApplicationConfig& out);
		protected:
			bool Startup(const TGL::OS::APPLICATION_PARAM& aParam);
			void Shutdown(const TGL::OS::APPLICATION_PARAM& aParam);

		private:
			virtual void Initialize() = 0;
			virtual void CleanUp() = 0;
			virtual bool Update(float fDeltaTime) = 0;
			virtual void Draw() = 0;
		public:	
			int Run(const TGL::OS::APPLICATION_PARAM& aParam);
		public:
			void OnInputRecive(WPARAM wParam, LPARAM lParam);
		public:
			static LRESULT CALLBACK MainWndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);
			LRESULT CALLBACK AppWndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);
	};
}
#endif //TGL_BUILD_WINDOWS
#endif //APPLICATION_HPP