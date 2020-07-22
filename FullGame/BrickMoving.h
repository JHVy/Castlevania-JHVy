#ifndef __BRICKMOVING_H_

#define __BRICKMOVING_H_




#include "Brick.h"

class BrickMoving : public Brick
{
public:
	BrickMoving(float _x, float _y, int id = 0, int type = 0, float width = 32, float height = 32);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};
#endif // !__BRICKMOVING_H_
