#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMIII_WIDTH 27
#define ITEMII_HEIGHT 27

class Item;

class ItemIII : public Item
{
public:
	ItemIII(float _x, float _y) : Item(_x, _y)
	{
		this->numAnimation = 716;
		AddAnimation(716);
		this->itemType = eType::ITEMIII;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

