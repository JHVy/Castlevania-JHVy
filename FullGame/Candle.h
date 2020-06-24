#pragma once

#include "ItemHeart.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemBoongmerang.h"

#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32

#define CANDLE_STATE_NOT_EXSIST 0
#define CANDLE_STATE_EXSIST 1
#define CANDLE_STATE_ITEM 2
#define CANDLE_STATE_ITEM_NOT_EXSIST 3

#define ID_HEART		1
#define ID_SMAILLHEART	2
#define ID_BOONGMERANG	3


class Item_Heart;
class Iteam_SmallHeart;
class Item;

class Candle : public CGameObject
{
private:
	int numAnimation = 0;
	Item* item;

public:
	Candle(int _x, int _y) {
		
		this->_type = eType::CANDLE;
		x = _x;
		y = _y;
		this->numAnimation = 502;
		this->state = CANDLE_STATE_EXSIST;
	}

	Candle(int _x, int _y, int _id_item) {
		x = _x;
		y = _y; 
		this->numAnimation = 502;
		this->_type = eType::CANDLE;

		switch (_id_item) 
		{
		case ID_HEART:
			item = new Item_Heart(x, y);
			return;

		case ID_BOONGMERANG:
			item = new ItemBoongmerang(x, y);
			return;

		/*case ID_SMAILLHEART: 
			item = new Iteam_SmallHeart(x, y);
			return;*/

		default:
			item = NULL;
			return;
		}
	}

public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int getItemType() {
		return this->item->getItemType();
	}

	void invisibleItem() {
		this->item->StartInvisible();
	}
};

