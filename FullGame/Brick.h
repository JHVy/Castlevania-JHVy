#ifndef __BRICK_H_

#define __BRICK_H_




#include "GameObject.h"
#include "Textures.h"
#include "Define.h"

class Brick : public CGameObject
{
public:
	Brick(float _x, float _y, int id = 0, int type = 0, float width = 32, float height = 32);
	virtual void Render();
};
#endif // !__BRICK_H_
