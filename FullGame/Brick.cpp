#include "Brick.h"

Brick::Brick(float _x, float _y, int id , int type, float width, float height) : CGameObject(_x, _y)
{
	this->_type = eType::BRICK_2;

	w = width;
	h = height;
}

void Brick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + w;
	bottom = y + h;
}

void Brick::Render()
{
	//RenderBoundingBox();
}

