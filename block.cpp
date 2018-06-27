
#include "block.h"

//class that stores the x and y positions of the individual pikachu heads/blocks

Block::Block(int x, int y)
{
	_x = x;
	_y = y;
}

int Block::getX()
{
	return _x;
}

int Block::getY()
{
	return _y;
}