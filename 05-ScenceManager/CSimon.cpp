#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "CSimon.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"


CSimon::CSimon(float x, float y) : CGameObject()
{
	SetState(SIMON_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//update lai vi tri cua simon khi no chay ra khoi screen
	if (x <= 0)
	{
		x = 1;
	}
	else if (x >= 740)
	{
		x = 740;
	}

	if (GetState() == SIMON_STATE_ATTACK)
	{
		vx = 0;
		int ani;
		if (nx < 0)
		{
			ani = SIMON_STATE_ATTACK; // QUAY TRAI
		}
		else
		{
			ani = SIMON_ANI_ATTACK_RIGHT; // QUAY PHAI
		}
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (isJumping) {
		if (timerJump < 800)
			timerJump += dt;
		else
		{
			timerJump = 0;
			isJumping = false;
			//SetState(Simon_STATE_IDLE);
		}
	}


	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				// if Goomba
				else if (dynamic_cast<CPortal*>(e->obj))
				{
					CPortal* p = dynamic_cast<CPortal*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CSimon::Render()
{
	int ani = -1;
	if (state == SIMON_STATE_DIE)
	{
		ani = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_SIT)
	{
		if (nx < 0)
		{
			ani = SIMON_ANI_SIT_LEFT;
			if (isAttack)
			{
				ani = SIMON_ANI_SIT_ATTACK_LEFT;
			}
		}
		else
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (nx < 0)
		{
			ani = SIMON_ANI_JUMP_LEFT;
		}
		else
		{
			ani = SIMON_ANI_JUMP_RIGHT;
		}
	}
	else if (state == SIMON_STATE_ATTACK)
	{
		if (nx < 0)
		{
			ani = SIMON_ANI_ATTACK;
		}
		else
		{
			ani = SIMON_ANI_ATTACK_RIGHT;
		}
	}
	else
	{
		if (vx == 0)
		{
			if (nx < 0)
			{
				ani = SIMON_ANI_IDLE_LEFT; 
			}
			else
			{
				ani = SIMON_ANI_IDLE_RIGHT;
			}
		}
		else if (vx > 0)
		{
			if (isJumping == false)
			{
				ani = SIMON_ANI_WALKING_LEFT; // SIMON_ANI_WALKING_RIGHT; // neu dang nhay thi ko update ani walk
			}
			else
			{
				ani = SIMON_ANI_JUMP_RIGHT;
			}
		}
		else if (vx < 0)
		{
			if (isJumping == false)
			{
				ani = SIMON_ANI_WALKING_RIGHT;
			}
			else
			{
				ani = SIMON_ANI_JUMP_LEFT;
			}
		}

	}

	//ani = SIMON_ANI_DIE; //SIMON_ANI_SIT_ATTACK_LEFT;
	//nx = 1;

	int alpha = 255;

	animation_set->at(ani)->Render(x, y, alpha, nx);
	//animation_set->

	RenderBoundingBox();
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == SIMON_STATE_SIT)
	{
		left = x;
		top = y + 6;
	}
	else
	{
		left = x;
		top = y;
	}

	right = x + SIMON_BIG_BBOX_WIDTH;
	bottom = y + SIMON_BIG_BBOX_HEIGHT;
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
	{
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	}
	case SIMON_STATE_WALKING_LEFT:
	{
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	}
	case SIMON_STATE_JUMP:
	{
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	}
	case SIMON_STATE_IDLE:
	{
		vx = 0;
		break;
	}
	case SIMON_STATE_DIE:
	{
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
	}
}

//void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
//{
//	left = x;
//	top = y; 
//
//	if (level==SIMON_LEVEL_BIG)
//	{
//		right = x + SIMON_BIG_BBOX_WIDTH;
//		bottom = y + SIMON_BIG_BBOX_HEIGHT;
//	}
//	else
//	{
//		right = x + SIMON_SMALL_BBOX_WIDTH;
//		bottom = y + SIMON_SMALL_BBOX_HEIGHT;
//	}
//}

/*
	Reset Mario status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

