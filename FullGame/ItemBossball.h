#pragma once
#ifndef __ITEMBOSSBALL_H_
#define __ITEMBOSSBALL_H_



#include "GameObject.h"
#include "Simon.h"
#include "Textures.h"
#include "Item.h"

#define ITEMBOSSBALL_WIDTH 32
#define ITEMBOSSBALL_HEIGHT 32


class ItemBossBall : public Item
{
public:
	ItemBossBall(float _x, float _y) : Item(_x, _y)
	{
		AddAnimation(712);
		_type = eType::BOSSBALL;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};
#endif // !__ITEMBOSSBALL_H_