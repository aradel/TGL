#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H


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