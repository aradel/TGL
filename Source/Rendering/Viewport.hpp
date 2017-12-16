#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include <d3d12.h>
#include "../TGL.hpp"
namespace TGL 
{
	struct Viewport 
	{
		uint16 xTop = 0;
		uint16 yTop = 0;
		uint16 xBottom = 0;
		uint16 yBottom = 0;
		
		Viewport();
		Viewport(uint16 xTop, uint16 yTop, uint16 xBottom, uint16 yBottom);
		~Viewport();
	};
}
#endif