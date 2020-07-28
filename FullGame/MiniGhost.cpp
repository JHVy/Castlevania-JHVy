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
	
	if (x > 4000)
	{
		_leftLimit = SCENCE_4_LEFT;
		_rightLimit = SCENCE_4_RIGHT - SCREEN_WIDTH * 3 / 2;
	}
	else
	{
		_leftLimit = SCENCE_1_LEFT;
		_rightLimit = SCENCE_1_RIGHT - MINIGHOST_BBOX_WIDTH;
	}
}

void MiniGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;

	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
		}
		else
		{
			float xSimon, ySimon;
			Simon::GetInstance()->GetPosition(xSimon, ySimon);


			CGameObject::Update(dt);
			x += dx;
			y += dy;

			ChasingSimon(xSimon, ySimon);
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

void MiniGhost::ChasingSimon(int xS, int yS)
{
	if (x < xS)
	{
		if (abs(xS - x) > 40)
		{
			vx = GHOST_SPEED;
			nx = 1;
		}
	}
	else if (x > xS)
	{
		if ((abs(xS - x) > 40))
		{
			vx = -GHOST_SPEED;
			nx = -1;
		}
	}


	if (yS - 20 > y)
		vy = VY_GHOST
	else if (yS + 20 < y)
		vy = -VY_GHOST;
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
