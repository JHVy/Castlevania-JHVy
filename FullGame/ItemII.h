#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMII_WIDTH 27
#define ITEMII_HEIGHT 27

class Item;

class ItemII : public Item
{
public:
	ItemII(float _x, float _y) : Item(_x, _y)
	{
		this->numAnimation = 713;
		AddAnimation(713);
		this->itemType = eType::ITEMII;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

