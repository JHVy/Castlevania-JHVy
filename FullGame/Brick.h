#ifndef __BRICK_H_

#define __BRICK_H_




#include "GameObject.h"
#include "Textures.h"
#include "Define.h"

class Brick : public CGameObject
{
private:
	float w, h;

public:
	Brick(float _x, float _y, int id = 0, int type = 0, float width = 32, float height = 32);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
};
#endif // !__BRICK_H_
