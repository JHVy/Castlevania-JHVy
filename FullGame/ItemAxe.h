#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEM_AXE_WIDTH 32
#define ITEM_AXE_HEIGHT 32

class Item;

class ItemAxe : public Item
{
public:
	ItemAxe(float _x, float _y) : Item(_x, _y)
	{
		this->numAnimation = 710;
		AddAnimation(710);
		this->itemType = eType::ITEMAXE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

