#ifndef RENDER_DEVICE_HPP
#define RENDER_DEVICE_HPP

#include "../Interface/IRenderDevice.hpp"
#include "../../Rendering/Viewport.hpp"
#include "../../TGL.hpp"

#include <memory>
namespace TGL 
{
#ifdef TGL_BUILD_WINDOWS
	struct DXGIContext;
#endif
	class CommandList;


	typedef std::shared_ptr<CommandList> CommandListPtr;
	class RenderDevice : public TGL::IRenderDevice
	{
		protected:
			float clearColor[4];
			TGL::DisplayInfo displayInfo;
			TGL::GraphicsCardInfo gfxCardInfo;
			TGL::RendererDeviceType type;
		public:
			void SetClearColor(float r, float g, float b);

			const TGL::DisplayInfo GetDisplayInfo();
			const TGL::GraphicsCardInfo GetGraphicsInfo();
			const TGL::RendererDeviceType GetDeviceType();
		public:
			virtual bool Initialize(const TGL::RenderDeviceParameter& param, const TGL::GraphicsSettings& settings) override = 0;
			virtual void Shutdown() = 0;

			virtual TGL::CommandListPtr CreateCommandList() = 0;
			virtual void ExecuteCommandList(TGL::CommandList* pCmdList) = 0;
			
			virtual void OnScreenSizeChanged(const TGL::ScreenSize& size) = 0;
			virtual void OnSettingsChanged(const TGL::GraphicsSettings& settings) = 0;

			//virtual void* GetNativeDevice() = 0;
	};
}

#endif