#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMVASE_WIDTH 27
#define ITEMVASE_HEIGHT 35

class Item;

class ItemVase : public Item
{
public:
	ItemVase(float _x, float _y) : Item(_x, _y)
	{
		this->numAnimation = 717;
		AddAnimation(717);
		this->itemType = eType::ITEMVASE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

