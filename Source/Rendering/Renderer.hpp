#ifndef RENDERER_H
#define RENDERER_H
#include "ResourcePool.hpp"
#include "../Rendering/Viewport.hpp"
#include "../Rendering/BackBuffer.hpp"
#include "../Rendering/CommandList.hpp"
#include "../Rendering/SwapChain.hpp"
#include "../Application/Settings.hpp"
#include "../TGL.hpp"
namespace TGL 
{
	class GraphicsDevice;
	class ResourcePool;
	struct RendererParameter
	{
		TGL::GraphicsSettings gfxSettings;
		TGL::GraphicsDevicePtr pDevice;
	};

	class Renderer 
	{
		private:
			TGL::GraphicsSettings settings;
			TGL::BackBuffer backBuffer;
			TGL::SwapChain swapChain;
			TGL::ViewPort viewport;
			
			TGL::CommandListPtr pCmdList = nullptr;

			float clearColor[4];
		public:
			Renderer() = default;
			~Renderer() = default;

			bool Initialize(TGL::ResourcePool& resourcePool, const TGL::RendererParameter& param);
			void Shutdown();

			void SetClearColor(float r, float g, float b);
		public:
			void OnScreenSizeChaged();
			void OnSettingsChanged(const TGL::GraphicsSettings settings);

	};
}

#endif