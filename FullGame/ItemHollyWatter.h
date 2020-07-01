#pragma once

#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEM_HOLLYWATTER_WIDTH 35
#define ITEM_HOLLYWATTER_HEIGHT 27

class Item;

class ItemHollyWatter : public Item
{
public:
	ItemHollyWatter(float _x, float _y) : Item(_x, _y)
	{
		this->numAnimation = 714;
		AddAnimation(714);
		this->itemType = eType::ITEMHOLLYWATTER;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
