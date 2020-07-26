#pragma once
#include "GameObject.h"
#include "Define.h"

class CHidenObject : public CGameObject
{
private:
	int _autoX;
	int ny;
public:

	CHidenObject(float _x, float _y, int w, int h, int type, int trendX = 0, int trendY = 0) :CGameObject(_x, _y, type, w, h)
	{
		this->_type = type;
		nx = trendX;
		ny = trendY;
		this->state = state;
	}

	void Render();
	int getNx() { return nx; }
	int getNy() { return ny; }
	int GetAutoX() { return _autoX; }
};