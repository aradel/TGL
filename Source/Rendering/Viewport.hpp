#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include <d3d12.h>
#include "../TGL.hpp"
namespace TGL 
{
	struct Viewport 
	{
		uint16 xTopLeft = 0;
		uint16 yTopLeft = 0;
		uint16 xWidth = 0;
		uint16 yHeight = 0;
		
		Viewport();
		Viewport(uint16 xTopLeft, uint16 yTopLeft, uint16 xWidth, uint16 yHeight);
		~Viewport();
	};
}
#endif