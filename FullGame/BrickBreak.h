#pragma once
#include"Candle.h"

class BrickBreak : public Candle
{
public:
	int IdBrick;
	virtual void Hurt();
	virtual void Render();
	void RenderBlackBox();

	BrickBreak(float _x, float _y, int w, int h, int IdBrick, int id = 0) : Candle(_x, _y, id, w, h)
	{
		this->_type = eType::BRICKBREAK;
		this->IdBrick = IdBrick;
	}
};