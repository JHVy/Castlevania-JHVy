#include "MiniGhost.h"


#include "HidenObject.h"
#include "Brick.h"
#include"Torch.h"
#include "Game.h"

MiniGhost::MiniGhost(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	this->_type = eType::MINIGHOST;
	animations.clear();
	AddAnimation(1006);
	AddAnimation(800);
	AddAnimation(802);
	nx = -1;
	SetSpeed(GetTrend() * MINIGHOST_SPEED, 0);
	dt_appear = 0;
}
void MiniGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);

	if (dt_appear > 0)
	{
		if (GetTickCount() - dt_appear > TIME_APPEAR && (start_x > cam_x + SCREEN_WIDTH) || (start_x < cam_x))
		{
			state = CANDLE_STATE_EXSIST;
			vx = nx * MINIGHOST_SPEED;
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
		if (state == CANDLE_STATE_EXSIST) // dang o dang con minighost
		{
			x += dx;

			CGameObject::Update(dt);

		}
		else if (state == CANDLE_STATE_ITEM) // simon va cham minighost -> danh roi item
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

void MiniGhost::Render()
{
	if (!this->IsStart())
		return;

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

bool MiniGhost::IsStart()
{
	//isStart = false;
	float x, y;
	Simon::GetInstance()->GetPosition(x, y);

	if (x < 1100)
		Start();
	
	return isStart;
}

void MiniGhost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == CANDLE_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + MINIGHOST_BBOX_WIDTH;
		bottom = y + MINIGHOST_BBOX_HEIGHT;
	}
	else if (state == CANDLE_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void MiniGhost::CollisionWithBrick(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{


	/*if (ny != 0) vy = 0;
	if (vx == 0)
		vx = -MINIGHOST_SPEED;*/
}
