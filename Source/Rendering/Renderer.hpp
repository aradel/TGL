#ifndef RENDERER_H
#define RENDERER_H
#include "ResourcePool.hpp"
#include "../Devices/Render/RenderDevice.hpp"
#include "../Application/Settings.hpp"
#include "../TGL.hpp"
namespace TGL 
{
	struct RendererParameter
	{
		TGL::GraphicsSettings gfxSettings;
		TGL::RenderDevice* pDevice;
	};

	class Renderer 
	{
		private:
			TGL::GraphicsSettings settings;
			TGL::ViewPort viewport;
			
			TGL::CommandListPtr pCmdList;
		public:
			Renderer() = default;
			~Renderer() = default;

			bool Initialize(const TGL::RendererParameter& param);
			void Shutdown();
		public:
			void OnScreenSizeChaged();
			void OnSettingsChanged(const TGL::GraphicsSettings settings);

	};
}

#endif