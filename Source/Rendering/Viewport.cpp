#include "Viewport.hpp"

TGL::Viewport::Viewport() 
{
	
}

TGL::Viewport::Viewport(uint16 xTopLeft, uint16 yTopLeft, uint16 xWidth, uint16 yHeight)
{
	this->xTopLeft = xTopLeft;
	this->yTopLeft = yTopLeft;
	this->xWidth = xWidth;
	this->yHeight = yHeight;
}

TGL::Viewport::~Viewport() 
{

}
