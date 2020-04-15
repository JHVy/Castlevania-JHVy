#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_ATTACK		700

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3


#define SIMON_ANI_JUMP_RIGHT		4
#define SIMON_ANI_JUMP_LEFT			5
#define SIMON_ANI_SIT_RIGHT			6
#define SIMON_ANI_SIT_LEFT			7

#define SIMON_ANI_ATTACK			9
#define SIMON_ANI_ATTACK_RIGHT		10
#define SIMON_ANI_SIT_ATTACK_LEFT	11



#define SIMON_ANI_DIE				8

#define SIMON_BIG_BBOX_WIDTH  15
#define SIMON_BIG_BBOX_HEIGHT 27



class CSimon : public CGameObject
{

	float start_x;			// initial position of Simon at scene
	float start_y;
public:
	CSimon(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	boolean isJumping = false;
	boolean isFlip = true;
	DWORD timerJump = 0;
	boolean isAttack;
};