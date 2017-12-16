#include "Viewport.hpp"

TGL::Viewport::Viewport() 
{
	
}

TGL::Viewport::Viewport(uint16 xTop, uint16 yTop, uint16 xBottom, uint16 yBottom) 
{
	this->xTop = xTop; 
	this->yTop = yTop;
	this->xBottom = xBottom;
	this->yBottom = yBottom;
}

TGL::Viewport::~Viewport() 
{

}
