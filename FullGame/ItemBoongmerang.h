#pragma once
#include "Define.h"
#include "Item.h"

#define ITEMBOONGMERANG_WIDTH 32
#define ITEMBOONGMERANG_HEIGHT 32

class Item;

class ItemBoongmerang : public Item
{
public:
	ItemBoongmerang(int _x, int _y) : Item(_x, _y) {
		this->numAnimation = 719;
		AddAnimation(719);
		this->itemType = eType::ITEMBOONGMERANG;
	}

public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

