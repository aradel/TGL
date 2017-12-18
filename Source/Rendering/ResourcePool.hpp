#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include "../Devices/Render/RenderDeviceD3D12.hpp"

namespace TGL 
{
	class ResourcePool
	{
		private:
			//TGL::DescriptorHeapCollection descriptorCollection;
		public:
			bool Initialize();
			void Shutdown();

	};
}

#endif