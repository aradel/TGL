#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H
//#include "DescriptorHeap.hpp"
#include  "../TGL.hpp"
namespace TGL 
{
	class ResourcePool
	{
		private:
			//TGL::DescriptorHeapCollection descriptorCollection;
		public:
			virtual bool Initialize(TGL::GraphicsDevicePtr pDevice);
			virtual void Shutdown();
	};


}

#endif