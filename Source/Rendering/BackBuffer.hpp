#ifndef BACKBUFFER_HPP
#define BACKBUFFER_HPP
#include "DescriptorHeap.hpp"
#include "RenderTarget.hpp"
#include <vector>
namespace TGL
{
	struct BackBuffer
	{
		//TGL::DescriptorHeap bbHeap; //Move to General allocator
		size_t nBackBuffers = 0;
		RenderTarget renderTarget[3];
	};
}
#endif