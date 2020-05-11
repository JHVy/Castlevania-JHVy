#pragma once

#include "Define.h"
#include "Item.h"

#define ITEMDAGGER_WIDTH 32
#define ITEMDAGGER_HEIGHT 32

class Item;

class ItemDagger : public Item
{
public:
	ItemDagger(int _x, int _y) : Item(_x, _y) {
		this->numAnimation = 701;
		AddAnimation(701);

	}

public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};



