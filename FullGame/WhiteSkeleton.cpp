#include"WhiteSkeleton.h"
#include "HidenObject.h"
#include "Brick.h"
#include"Torch.h"
#include "Game.h"

WhiteSkeleton::WhiteSkeleton(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	this->_type = eType::WHITESKELETON;
	animations.clear();
	AddAnimation(1004);
	AddAnimation(800);
	AddAnimation(802);
	nx = 1;
	SetSpeed(GetTrend() * WHITESKELETON_SPEED, 0);
	dt_appear = 0;
	if (x > 4000)
	{
		_leftLimit = SCENCE_4_LEFT;
		_rightLimit = SCENCE_4_RIGHT - SCREEN_WIDTH * 3 / 2;
	}
	else
	{
		_leftLimit = SCENCE_1_LEFT;
		_rightLimit = SCENCE_1_RIGHT - WHITESKELETON_BBOX_WIDTH;
	}
}
void WhiteSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);

	if (dt_die == 0)
	{
		if (state == CANDLE_STATE_EXSIST)
		{
			if ((x < _leftLimit && nx < 0) || (x > _rightLimit && nx > 0))
			{
				nx = -nx;
				vx = -vx;
			}

			if (x < cam_x - WHITESKELETON_DISTANCE_TOO_FAR || x > cam_x + SCREEN_WIDTH + WHITESKELETON_DISTANCE_TOO_FAR)
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
					if (coObjects->at(i)->GetState() == eType::OBJECT_HIDDEN_WHITESKELETON)
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

				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (ny != 0)
					vy = 0;
				isGrounded = true;
				if (nx != 0)
					vx *= -1;

			}

			float xSimon, ySimon;
			Simon::GetInstance()->GetPosition(xSimon, ySimon);

			ChasingSimon(xSimon, ySimon);

			if (coEvents.size()  == 0)
			{
				enemyState = JUMP;
				vy = -0.1;
				isGrounded = false;
			}
			else {
				enemyState = WALK;
			}

			//list.clear();
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) 
				delete coEvents[i];

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

void WhiteSkeleton::Render()
{
	//if (x == 0 && y == 0)
	//	return;

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
void WhiteSkeleton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == CANDLE_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + WHITESKELETON_BBOX_WIDTH;
		bottom = y + WHITESKELETON_BBOX_HEIGHT;
	}
	else if (state == CANDLE_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
//void WhiteSkeleton::CollisionWithBrick(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
//{
//
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//	vector<LPGAMEOBJECT> list;
//	list.push_back((LPGAMEOBJECT)(obj));
//	// turn off collision when die 
//
//	CalcPotentialCollisions(&list, coEvents);
//
//	float min_tx, min_ty, nx = 0, ny;
//
//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//
//	//// block 
//	if (min_tx <= min_tx0)
//		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
//	if (min_ty <= min_ty0)
//		y += min_ty * dy + ny * 0.4f;
//	if (ny != 0) vy = 0;
//	if (vx == 0)
//		vx = -WHITESKELETON_SPEED;
//	list.clear();
//}
//
//void WhiteSkeleton::CollisionWithHiden(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
//{
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//
//	vector<LPGAMEOBJECT> list;
//	list.push_back((LPGAMEOBJECT)(obj));
//	// turn off collision when die 
//
//	CalcPotentialCollisions(&list, coEvents);
//
//	float min_tx, min_ty, nx = 0, ny;
//
//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//
//	//// block 
//
//	// clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//	CHidenObject* ohiden = dynamic_cast<CHidenObject*>(obj);
//	if (ohiden->GetState() == eType::OBJECT_HIDDEN_WHITESKELETON)
//	{
//		vx = 0;
//		vy = WHITESKELETON_SPEED * 2;
//		y += vy * dt;
//		x += vx * dt;
//	}
//	else
//	{
//		x += vx * dt;
//
//	}
//
//	ohiden = NULL;
//	list.clear();
//}

bool WhiteSkeleton::IsStart()
{
	if (this->DistanceTo(Simon::GetInstance()) <= AREA_ACTIVE)
		isStart = true;

	return isStart;
}

void WhiteSkeleton::ChasingSimon(int xs, int ys)
{
	if (enemyState == JUMP)
		return;

	if (xs > x && abs(xs - x) > AREA_TURNING1)
	{
		nx = 1;
		vx = SKELETON_SPEED_X;
	}
	else if (xs > x && abs(xs - x) < AREA_TURNING2)
	{
		nx = 1;
		vx = -SKELETON_SPEED_X;
	}
	else if (xs < x && abs(xs - x) > AREA_TURNING3)
	{
		nx = -1;
		vx = -SKELETON_SPEED_X;
	}
	else if (xs < x && abs(xs - x) < AREA_TURNING4)
	{
		nx = -1;
		vx = SKELETON_SPEED_X;
	}
}