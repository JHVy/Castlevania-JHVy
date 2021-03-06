#include"Fleaman.h"
#include "HidenObject.h"
#include "Brick.h"
#include"Torch.h"
#include "Game.h"

Fleaman::Fleaman(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	firstJump = false;
	isGrounded = true;
	this->_type = eType::FLEAMAN;
	animations.clear();
	AddAnimation(1007);
	AddAnimation(800);
	AddAnimation(802);
	nx = 1;
	SetSpeed(GetTrend() * FLEAMAN_SPEED, 0);
	dt_appear = 0;
	if (x > 4000)
	{
		_leftLimit = SCENCE_4_LEFT;
		_rightLimit = SCENCE_4_RIGHT - SCREEN_WIDTH * 3 / 2;
	}
	else
	{
		_leftLimit = SCENCE_1_LEFT;
		_rightLimit = SCENCE_1_RIGHT - FLEAMAN_BBOX_WIDTH;
	}
	
}
void Fleaman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);

	//if (dt_appear > 0)
	//{
	//	if (start_x > cam_x + SCREEN_WIDTH + FLEAMAN_DISTANCE_TOO_FAR || start_x < cam_x - FLEAMAN_DISTANCE_TOO_FAR)
	//		return;

	//	if (GetTickCount() - dt_appear > TIME_APPEAR && (start_x > cam_x + SCREEN_WIDTH) || (start_x < cam_x))
	//	{

	//		float s_x, s_y;
	//		Simon::GetInstance()->GetPosition(s_x, s_y);
	//		state = CANDLE_STATE_EXSIST;
	//		x = start_x;
	//		y = start_y;
	//		if (x > s_x)
	//			nx = -1;
	//		else
	//			nx = 1;
	//		vx = nx * FLEAMAN_SPEED;

	//		if (item)
	//			item->SetState(ITEM_STATE_EXSIST);
	//		dt_appear = 0;
	//		dt_die = 0;
	//	}
	//	else
	//		return;
	//}

	if (dt_die == 0)
	{
		if (state == CANDLE_STATE_EXSIST)
		{
			if ((x < _leftLimit && nx < 0) || (x > _rightLimit && nx > 0))
			{
				nx = -nx;
				vx = -vx;
			}

			if (x < cam_x - FLEAMAN_DISTANCE_TOO_FAR || x > cam_x + SCREEN_WIDTH + FLEAMAN_DISTANCE_TOO_FAR)
			{
				state = CANDLE_STATE_ITEM_NOT_EXSIST;
				dt_appear = GetTickCount();
			}
			vector<LPGAMEOBJECT> list;
			for (int i = 0; i < coObjects->size(); i++)
			{

				if (dynamic_cast<Brick*>(coObjects->at(i)))
				{
					list.push_back(coObjects->at(i));
				}
				else if (dynamic_cast<CHidenObject*>(coObjects->at(i)))
				{
					if (coObjects->at(i)->GetState() == eType::OBJECT_HIDDEN_FLEAMAN)
						list.push_back(coObjects->at(i));
				}
			}

			vy += SIMON_GRAVITY * dt;

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
						if (e->ny != 0)
						{
							if (e->ny == -1)
							{
								isGrounded = true;
								vy = 0;
							}
							else
								y += dy;
						}

						CollisionWithBrick(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}
					if (dynamic_cast<CHidenObject*>(e->obj))
					{
						CollisionWithHiden(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}

				}

			}
			if ( this->DistanceTo(Simon::GetInstance()) - x < 150 || firstJump )
			{
				if (!firstJump)
				{
					vx = FLEAMAN_SPEED;
					enemyState = JUMP_HIGH;
					vy = FLEAMAN_SPPED_Y_HIGH;
					isGrounded = false;
					firstJump = true;
				}
				else
				{
					float xSimon, ySimon;
					Simon::GetInstance()->GetPosition(xSimon, ySimon);

					ChasingSimon(xSimon, ySimon);
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
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > TIME_ENEMY_DIE) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
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
		top = y;
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

void Fleaman::CollisionWithHiden(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
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

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CHidenObject* ohiden = dynamic_cast<CHidenObject*>(obj);
	if (ohiden->GetState() == eType::OBJECT_HIDDEN_FLEAMAN)
	{
		vx = 0;
		vy = FLEAMAN_SPEED * 2;
		y += vy * dt;
		x += vx * dt;
	}
	else
	{
		x += vx * dt;

	}

	ohiden = NULL;
	list.clear();
}

void Fleaman::ChasingSimon(int xs, int ys)
{
	if (x < xs && abs(xs - x) > AREA_TURNING)
	{
		vx = FLEAMAN_SPEED;
		nx = 1;

	}
	else if (x > xs && (abs(xs - x) > AREA_TURNING))
	{
		vx = -FLEAMAN_SPEED;
		nx = -1;
	}

	if ((rand() % JUMP_RATE_MAX < JUMP_RATE))
	{
		if (!isGrounded)
			return;

		if (rand() % 4 == 3)
		{
			enemyState = JUMP_HIGH;
			vy = FLEAMAN_SPPED_Y_HIGH;
			isGrounded = false;
		}
		else
		{
			enemyState = JUMP_LOW;
			vy = FLEAMAN_SPEED_Y_LOW;
			isGrounded = false;
		}

	}
}