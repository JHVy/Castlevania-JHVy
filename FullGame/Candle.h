#pragma once

#include "ItemHeart.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemBoongmerang.h"
#include "ItemAxe.h"
#include "ItemII.h"
#include "ItemBoongmerang.h"
#include "ItemHollyWatter.h"
#include "ItemIII.h"
#include "ItemVase.h"
#include "ItemSmallHeart.h"
#include "ItemMoney.h"

#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32

#define CANDLE_STATE_NOT_EXSIST 0
#define CANDLE_STATE_EXSIST 1
#define CANDLE_STATE_ITEM 2
#define CANDLE_STATE_ITEM_NOT_EXSIST 3

#define ID_HEART		1 // --
#define ID_SMAILLHEART	2
#define ID_BOONGMERANG	3 // --
#define ID_MONEY_1		4  //100
#define ID_MONEY_2		5  //400
#define ID_MONEY_3		6 //700
#define ID_MONEY_4		7  //1000
#define ID_II			8 // --
#define ID_HOLLYWATTER	9 // --
#define ID_III			10 // --
#define ID_AXE   		11 // --
#define ID_VASE			12 // -- cai binh -> tang hinh



class Item;

class Candle : public CGameObject
{
protected:
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
			item = new ItemHeart(x,y);
			return;
		case ID_BOONGMERANG:
			item = new ItemBoongmerang(x, y);
			return;
		case ID_SMAILLHEART: 
			item = new ItemSmallHeart(x, y);
			return;
		case ID_AXE:
			item = new ItemAxe(x,y);
			return;
		/*case ID_MONEY_1:
			item = new ItemMoney(x,y, eType::MONEY_1);
			return;
		case ID_MONEY_2:
			item = new ItemMoney(x, y, eType::MONEY_2);
			return;
		case ID_MONEY_3:
			item = new ItemMoney(x, y, eType::MONEY_3);
			return;
		case ID_MONEY_4:
			item = new ItemMoney(x, y, eType::MONEY_4);
			return;*/
		case ID_HOLLYWATTER:
			item = new ItemHollyWatter(x,y);
			return;
		case ID_II:
			item = new ItemII(x,y);
			return;
		case ID_III:
			item = new ItemIII(x,y);
			return;
		case ID_VASE:
			item = new ItemVase(x,y);
			return;

		default:
			//item = NULL;
			item = new ItemSmallHeart(x, y);
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

