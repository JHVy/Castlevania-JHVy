#include"Fleaman.h"
#include "HidenObject.h"
#include "Brick.h"
#include"Torch.h"
#include "Game.h"

Fleaman::Fleaman(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	this->_type = eType::FLEAMAN;
	animations.clear();
	AddAnimation(1007);
	AddAnimation(800);
	AddAnimation(802);
	nx = 1;
	SetSpeed(GetTrend() * FLEAMAN_SPEED, 0);
	dt_appear = 0;
	
}
void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);

	if (dt_appear > 0)
	{
		if (GetTickCount() - dt_appear > TIME_APPEAR && (start_x > cam_x + SCREEN_WIDTH) || (start_x < cam_x))
		{

			float s_x, s_y;
			Simon::GetInstance()->GetPosition(s_x, s_y);
			state = CANDLE_STATE_EXSIST;
			x = start_x;
			y = start_y;
			if (x > s_x)
				nx = -1;
			else
				nx = 1;
			vx = nx * FLEAMAN_SPEED;

			if (item)
				item->SetState(ITEM_STATE_EXSIST);
			dt_appear = 0;
			dt_die = 0;
		}
		else
			return;
	}

	if (vx == 0 && vy == 0)
		return;
	if (dt_die == 0)
	{
		if (state == CANDLE_STATE_EXSIST)
		{
			vector<LPGAMEOBJECT> list;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<Brick*>(coObjects->at(i)))
				{
					list.push_back(coObjects->at(i));
				}
			}

			vy += FLEAMAN_GRAVITY * dt;
			
			CGameObject::Update(dt);

			// Simple fall down
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();


			CalcPotentialCollisions(&list, coEvents);

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else {
				float min_tx, min_ty, nx = 0, ny_1;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny_1);

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<Brick*>(e->obj))
					{
						CollisionWithBrick(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}
				}

			}
			list.clear();
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

			//update item
			if (item != NULL)
			{
				item->SetPosition(x, y);
			}

		}
		else if (state == CANDLE_STATE_ITEM)
		{
			dt_die = GetTickCount();
			if (item)
			{
				item->SetPosition(x, y);
			}
			else
			{
				state = CANDLE_STATE_ITEM_NOT_EXSIST;
				dt_appear = GetTickCount();
				return;
			}
		}
	}
	else
	{
		if (item != NULL)
		{//co item

			if (GetTickCount() - dt_die > TIME_ENEMY_DIE) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				state = CANDLE_STATE_ITEM;
				if (item->GetState() == ITEM_STATE_NOT_EXSIST)
				{
					state = CANDLE_STATE_ITEM_NOT_EXSIST;
					dt_appear = GetTickCount();
					return;
				}
			}
		}
		else
		{
			state = CANDLE_STATE_ITEM_NOT_EXSIST;
			dt_appear = GetTickCount();
			return;
		}
	}

}

bool Fleaman::IsStart()
{
	if (this->DistanceTo(Simon::GetInstance()) <= 200)
		isStart = true;
	
	return isStart;
}

void Fleaman::Render()
{
	if (x == 0 && y == 0)
		return;

	if (state == CANDLE_STATE_EXSIST)
	{
		animations[0]->Render(x, y, nx, 255);
	}
	else if (state == CANDLE_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();
	}
	else
	{
		if (GetTickCount() - dt_die < TIME_ENEMY_DIE)
		{
			animations[1]->Render(x, y);
			if (animations[1]->GetCurrentFrame() > 0)
				animations[2]->Render(x - 2, y - 5);
		}
	}

	//RenderBoundingBox();
}
void Fleaman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == CANDLE_STATE_EXSIST)
	{
		left = x;
		top = y - 10;
		right = x + FLEAMAN_BBOX_WIDTH;
		bottom = y + FLEAMAN_BBOX_HEIGHT;
	}
	else if (state == CANDLE_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void Fleaman::CollisionWithBrick(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	vector<LPGAMEOBJECT> list;
	list.push_back((LPGAMEOBJECT)(obj));
	// turn off collision when die 

	CalcPotentialCollisions(&list, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	if (!Fleaman::IsStart())
	{
		return;
	}
	if (min_tx <= min_tx0)
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	if (min_ty <= min_ty0)
		y += min_ty * dy + ny * 0.4f;
	if (ny != 0) vy = 0;
	if (vx == 0)
		vx = -FLEAMAN_SPEED;
	list.clear();
}
