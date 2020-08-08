#include "Brick.h"

Brick::Brick(float _x, float _y, int id , int type, float width, float height) : CGameObject(_x, _y)
{
	this->_type = eType::BRICK_2;

	this->width = width;
	this->height = height;
}

void Brick::Render()
{
	//RenderBoundingBox();
}

void Brick::Disappear()
{
	this->width = 0;
	this->height = 0;
}

