#include "Viewport.hpp"

TGL::ViewPort::ViewPort()
{
	
}

TGL::ViewPort::ViewPort(uint16 xTopLeft, uint16 yTopLeft, uint16 xWidth, uint16 yHeight)
{
	this->xTopLeft = xTopLeft;
	this->yTopLeft = yTopLeft;
	this->xWidth = xWidth;
	this->yHeight = yHeight;
}

TGL::ViewPort::~ViewPort()
{

}