#ifndef RENDERER_H
#define RENDERER_H
#include "ResourcePool.hpp"
#include "../Rendering/Viewport.hpp"
#include "../Rendering/CommandList.hpp"
#include "../Application/Settings.hpp"
#include "../TGL.hpp"
namespace TGL 
{
	class GraphicsDevice;
	struct RendererParameter
	{
		TGL::GraphicsSettings gfxSettings;
		TGL::GraphicsDevice* pDevice;
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