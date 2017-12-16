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
		TGL::GraphicsSettings settings;
	};
	struct Viewport;
	class Renderer 
	{
		private:
			TGL::GraphicsSettings settings;
			TGL::Viewport viewport;
		public:
			Renderer() = default;
			~Renderer() = default;

			bool Initialize(const TGL::RendererParameter& param);
			void Shutdown();

			void SetViewport(const TGL::Viewport& viewport);
			TGL::Viewport GetViewport();
		public:
			void OnScreenSizeChaged();
			void OnSettingsChanged(const TGL::GraphicsSettings settings);

	};
}

#endif