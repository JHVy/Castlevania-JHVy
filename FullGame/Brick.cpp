#include "Brick.h"

void CBrick::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y - 16;
	r = x + 2000;
	b = y + BRICK_BBOX_HEIGHT;
}