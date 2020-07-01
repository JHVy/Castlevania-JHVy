#pragma once
#include "Item.h"

#define SMALLHEART_SPEED_X 0.03f
#define SMALLHEART_SPEED_Y 0.02f

class Item;

class ItemSmallHeart :public Item
{
	float left_limit;
	float right_limit;
public:
	ItemSmallHeart(float _x, float _y) : Item(_x, _y)
	{
		animations.clear();
		this->numAnimation = 703;
		AddAnimation(703);
		this->itemType = eType::SMALLHEART;
		vx = SMALLHEART_SPEED_X;
		vy = SMALLHEART_SPEED_Y;
		left_limit = x - 20;
		right_limit = x + 20;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

};
