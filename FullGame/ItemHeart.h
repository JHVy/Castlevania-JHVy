#pragma once

#include "Define.h"
#include "Item.h"

#define ITEMHEART_WIDTH 22
#define ITEMHEART_HEIGHT 25

class Item;

class Item_Heart: public Item
{
public:
	Item_Heart(int _x, int _y): Item(_x, _y) {
		this->numAnimation = 702;
		AddAnimation(702);
		this->itemType = eType::HEART;
	}

public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

