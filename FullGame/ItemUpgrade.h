#pragma once

#include "Define.h"
#include "Item.h"

#define ITEMUPGRADE_WIDTH 32
#define ITEMUPGRADE_HEIGHT 32

class Item;

class ItemUpgrade : public Item
{
public:
	ItemUpgrade(int _x, int _y) : Item(_x, _y) {
		this->numAnimation = 700;
		AddAnimation(700);

	}

public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};



