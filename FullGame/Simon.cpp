﻿#include "Simon.h"
//#include "Game.h"
#include "Sound.h"
#include "GameConfig.h"
#include "Axe.h"
#include "Dagger.h"
#include "Boongmerang.h"
#include "HolyWater.h"

Simon* Simon::_instance = NULL;

Simon* Simon::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Simon();
	}
	return _instance;
}

Simon::Simon() 
{
	weapons[eType::VAMPIREKILLER] = VampireKiller::GetInstance();

	untouchable = 0;
	trans_start = 0;
	start_jump = 0;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT_STAND;

	_energy = 16;
	_score = 0;
	_lives = 3;

	isOnStair = false;
	StairTrend = 0;
	listGameObj = NULL;

	weapons[eType::DAGGER] = Dagger::GetInstance();
	weapons[eType::AXE] = Axe::GetInstance();
	weapons[eType::HOLLYWATTER] = HollyWatter::GetInstance();
	weapons[eType::BOONGMERANG] = Boongmerang::GetInstance();
	
	SetState(SIMON_STATE_STAND_ATTACK); // set first to init
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->IsDie())
	{
		if (_lives > 0)
			_lives--;

		this->ResetLevel(GameConfig::GetInstance()->CurrentLevel);
		return;
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	if (isOnStair)
		vy = 0;

	if (start_jump > 0 && GetTickCount() - start_jump > SIMON_TIME_START_JUMP)
	{
		start_jump = 0;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE && !isOnStair)
		CalcPotentialCollisions(coObjects, coEvents);

	//Only keep check colission with Brick, else remove
	for (UINT i = 0; i < coEvents.size(); i++) 
		if (coEvents[i]->obj->GetType() != eType::BRICK_2)
			coEvents.erase(coEvents.begin() + i);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// collision simon with object item
	CollisionWithObjects(coObjects);


	// update weapon
	if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
	{
		VampireKiller::GetInstance()->SetPosition(GetXDraw(), y);
		weapons[eType::VAMPIREKILLER]->Update(dt, coObjects);
	}
	else if (_heart > 0 && state == SIMON_STATE_ATTACK_DAGGER)
	{
		if (this->GetCurrentWeapon()->GetState() == DAGGER_STATE_HIDE)
		//if (attack_start == 0)
		{
			//attack_start = GetTickCount();
			this->GetCurrentWeapon()->SetPosition(x, y);
			this->GetCurrentWeapon()->SetTrend(nx);
			this->GetCurrentWeapon()->SetState(DAGGER_STATE_ATTACK);
			ThrowWeapon();
		}
	}

	// simon attack
	if (attack_start) 
	{
		weapons[eType::VAMPIREKILLER]->SetUsing(true);

		int t = GetTickCount();
		if (t - attack_start > ATTACK_TIME) 
		{
			weapons[eType::VAMPIREKILLER]->SetUsing(false);
			attack_start = 0;
			//this->state = SIMON_STATE_IDLE;
		}
		return;
	}

	// simon invi because too hurt
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}


}

void Simon::ResetLevel(int level) 
{
	nx = StairTrend = 1;
	if (level == 3 || level == 5)
		isOnStair = true;
	else
		isOnStair = false;

	if (level == 5)
		nx = StairTrend = -1;

	GameConfig::GetInstance()->GetSimonPosition(x, y);
	vx = vy = 0;
	_energy = 16;


	/// DEBUG
	/*nx =1;
	x += 200;*/
}

void Simon::Render()
{
	int id;

	if (state == SIMON_STATE_DIE)
	{
		id = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_IDLE_DOWN)
	{
		id = SIMON_ANI_IDLE_DOWN;
	}
	else if (state == SIMON_STATE_IDLE_UP)
	{
		id = SIMON_ANI_IDLE_UP;
	}
	else if (state == SIMON_STATE_IDLE_DOWN)
	{
		id = SIMON_ANI_IDLE_DOWN;
	}
	else if (state == SIMON_STATE_IDLE_UP)
	{
		id = SIMON_ANI_IDLE_UP;
	}
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		id = SIMON_ANI_SITTING_ATTACKING;
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;

		if (start_jump)
			id = SIMON_ANI_SITTING_ATTACKING;

	}
	else if (state == SIMON_STATE_ATTACK_DAGGER)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
	}
	else if (state == SIMON_STATE_SIT)
	{
		id = SIMON_ANI_SITTING;

	}
	else if (state == SIMON_STATE_JUMP)
	{
		// neu dang nhay len 
		if (start_jump > 0 && GetTickCount() - start_jump < SIMON_TIME_STATE_JUMP)
			id = SIMON_ANI_JUMPING;
		else // dang roi xuong
			id = SIMON_ANI_IDLE;
	}
	else if (state == SIMON_STATE_GO_UP && isOnStair)
	{
		id = SIMON_ANI_GO_UP;
	}
	else if (state == SIMON_STATE_GO_DOWN)
	{
		if (isOnStair)
			id = SIMON_ANI_GO_DOWN;
		else
			id = SIMON_ANI_SITTING;
	}
	else 
	{
		if (vx == 0)
		{
			id = SIMON_ANI_IDLE;
		}
		else
		{
			id = SIMON_ANI_WALKING;
		}
	}


	if (trans_start > 0) {
		id = SIMON_ANI_TRANS;
	}
	int alpha = 255;

	//id = SIMON_ANI_STANDING_ATTACKING;
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);

	int x1 = GetXDraw(), y1 = y;

	if (untouchable) alpha = 128;


	//Draw Vampire
	if (state == SIMON_STATE_STAND_ATTACK || state == SIMON_STATE_SIT_ATTACK)
	{
		if (weapons[eType::VAMPIREKILLER] != NULL)
			weapons[eType::VAMPIREKILLER]->Render();
	}

	ani->Render(x1, y1, nx, alpha);
	//RenderBoundingBox();
}

int Simon::GetXDraw()
{
	int x_new = x;
	if (state == SIMON_STATE_STAND_ATTACK || state == SIMON_STATE_ATTACK_DAGGER)
	{
		x_new -= 10;
		if (GetTrend() == 1)
			x_new -= 8;
	} 
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		x_new -= 6;
		if (GetTrend() == 1)
			x_new -= 8;
	}

	return x_new;
}

void Simon::HackSimon()
{
	_heart = 50;
	_energy = 16;
	_lives = 50;
}

bool Simon::IsDie()
{
	if (y > 4 * SCREEN_HEIGHT || _energy <= 0)
	{
		Sound::GetInstance()->Play(eSound::musicLifeLost);
		return true;
	}

	return false;
}

void Simon::CollisionWithObjects(vector<LPGAMEOBJECT>* coObjects)
{
	if (!coObjects->empty()) 
	{
		Torch* torch;
		CHidenObject* hidenObj;
		Brick* brick;
		Candle* candle;
		Enemy* enemy;

		//duyet qua list object de check va cham va xu ly
		for (int index = 0; index < coObjects->size(); index++)
		{
			LPGAMEOBJECT obj = coObjects->at(index);

			if (!this->IsCollisedWith(obj))
				continue;	//ko va cham thi bo qua

			//va cham, check va xu ly voi cac loai obj
			switch (obj->_type)
			{
				case eType::TORCH:
					torch = (Torch*)obj;
					if (obj->GetState() == TORCH_STATE_ITEM) 
					{
						if (torch->getItemType() == eType::WHIPUPGRADE)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							VampireKiller::GetInstance()->setUpLevel();

						}
						else if (torch->getItemType() == eType::HEART)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_heart += 5;
						}
						else if (torch->getItemType() == eType::ITEMDAGGER)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							CBoard::GetInstance()->SetWeapon(eType::DAGGER);
						}

						torch->invisibleItem();
						torch->SetState(TORCH_STATE_NOT_EXSIST);
					}
					break;

				case eType::CANDLE:
				case eType::BRICKBREAK:
					candle = (Candle*)obj;
					if (obj->GetState() == CANDLE_STATE_ITEM)
					{
						if (candle->getItemType() == eType::HEART)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_heart += 5;
						}
						else if (candle->getItemType() == eType::SMALLHEART)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_heart++;
						}
						else if (candle->getItemType() == eType::MONEY_1)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 100;
						}
						else if (candle->getItemType() == eType::MONEY_2)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 400;
						}
						else if (candle->getItemType() == eType::MONEY_3)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 700;
						}
						else if (candle->getItemType() == eType::MONEY_4)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 1000;
						}
						else if (candle->getItemType() == eType::ITEMBOONGMERANG)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							CBoard::GetInstance()->SetWeapon(eType::BOONGMERANG);
						}
						else if (candle->getItemType() == eType::ITEMAXE)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							CBoard::GetInstance()->SetWeapon(eType::AXE);
						}
						else if (candle->getItemType() == eType::GATE)
						{
							Sound::GetInstance()->Play(eSound::soundOpenDoor);
						}
						else if (candle->getItemType() == eType::ITEMHOLLYWATTER)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							CBoard::GetInstance()->SetWeapon(eType::HOLLYWATTER);
						}
						else if (candle->getItemType() == eType::ITEMVASE)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}
						else if (candle->getItemType() == eType::ITEMII)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}
						else if (candle->getItemType() == eType::ITEMIII)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}

						candle->invisibleItem();
						candle->SetState(CANDLE_STATE_NOT_EXSIST);
					}
					break;

				case eType::GHOST:
				case eType::MINIGHOST:
				case eType::BLACKKNIGHT:
				case eType::RAVEN:
				case eType::FLEAMAN:
				case eType::WHITESKELETON:
				case eType::BAT:
				case eType::BOSS:
					enemy = (Enemy*)obj;
					if (obj->GetState() == CANDLE_STATE_EXSIST)		// Va cham GHOST -- khuc nay va cham với enemy 
					{
						if (enemy->Idle())
						{
							return;
						}

						if (!untouchable)
						{
							if (enemy->GetType() == eType::BAT)
							{
								enemy->Dead();
							}
							this->StartUntouchable();
							Sound::GetInstance()->Play(eSound::soundHurting);
							this->Hurt();
						}
					}
					else if (obj->GetState() == CANDLE_STATE_ITEM)
					{
						if (enemy->getItemType() == eType::HEART)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_heart += 5;
						}
						else if (enemy->getItemType() == eType::SMALLHEART)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_heart++;
						}
						else if (enemy->getItemType() == eType::MONEY_1)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 100;
						}
						else if (enemy->getItemType() == eType::MONEY_2)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 400;
						}
						else if (enemy->getItemType() == eType::MONEY_3)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 700;
						}
						else if (enemy->getItemType() == eType::MONEY_4)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							this->_score += 1000;
						}
						else if (enemy->getItemType() == eType::ITEMBOONGMERANG)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							CBoard::GetInstance()->SetWeapon(eType::BOONGMERANG);
						}
						else if (enemy->getItemType() == eType::ITEMAXE)
						{
							Sound::GetInstance()->Play(eSound::soundCollectWeapon);
							CBoard::GetInstance()->SetWeapon(eType::AXE);
						}
						else if (enemy->getItemType() == eType::GATE)
						{
							Sound::GetInstance()->Play(eSound::soundOpenDoor);
						}
						else if (enemy->getItemType() == eType::ITEMHOLLYWATTER)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
							CBoard::GetInstance()->SetWeapon(eType::HOLLYWATTER);
						}
						else if (enemy->getItemType() == eType::ITEMVASE)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}
						else if (enemy->getItemType() == eType::ITEMII)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}
						else if (enemy->getItemType() == eType::ITEMIII)
						{
							Sound::GetInstance()->Play(eSound::soundCollectItem);
						}

						enemy->invisibleItem();
						enemy->item->SetState(ITEM_STATE_NOT_EXSIST);
						enemy->SetState(CANDLE_STATE_NOT_EXSIST);
					}
					break;

				// Va cham cua qua man khac
				case eType::OBJECT_HIDDEN_DOOR:
					{	
						hidenObj = (CHidenObject*)obj;
						int gameLevel = hidenObj-> id_item;
						//DebugOut(L"[INFO] gameLevel: %d\n", gameLevel);
						Sound::GetInstance()->Play(eSound::musicStateClear);
						GameConfig::GetInstance()->SetGameLevel(gameLevel);
					}
					break;

				default:
					break;
			}
		}
	}
}

void Simon::CheckCollisionWithStair(int keyPress)
{
	if (listGameObj == NULL)
		return;

	for (int index = 0; index < listGameObj->size(); index++)
	{
		LPGAMEOBJECT obj = listGameObj->at(index);

		if (obj->GetType() != eType::STAIR_UP && obj->GetType() != eType::STAIR_DOWN)
			continue;	//ko phai STAIR thi bo qua

		if (keyPress == DIK_UP)
		{
			// Vao thang
			if (!isOnStair && obj->GetType() == eType::STAIR_UP && this->IsCollisedWith(obj))
			{
				isOnStair = true;
				StairTrend = obj->GetTrend();
				this->x = obj->x;
			}

			// Tren thang
			if (isOnStair)
			{
				this->SetState(SIMON_STATE_GO_UP);
			}

			//Ra khoi thang
			if (isOnStair && obj->GetType() == eType::STAIR_DOWN && this->IsCollisedWith(obj))
			{
				isOnStair = false;
				vx = vy = 0;
				y -= 20;	// tang y nhay len mot chut len de khoi overlap voi BRICK
			}
		}
		else if(keyPress == DIK_DOWN)
		{
			//if (IsJumping())
			//{
			//	return;
			//}


			// Vao thang
			if (!isOnStair && obj->GetType() == eType::STAIR_DOWN && this->IsCollisedWith(obj))
			{
				isOnStair = true;
				StairTrend = obj->GetTrend();
				this->x = obj->x;
			}

			// Tren thang
			if (isOnStair)
			{
				this->SetState(SIMON_STATE_GO_DOWN);
			}

			//Ra khoi thang
			if (isOnStair && obj->GetType() == eType::STAIR_UP && this->IsCollisedWith(obj))
			{
				isOnStair = false;
				vx = vy = 0;
			}
		}
	}
}

void Simon::CollisionWithItems(vector<LPGAMEOBJECT>* coObjects)
{

}

void Simon::ThrowWeapon()
{
	int idWeapon = CBoard::GetInstance()->GetWeapon();
	eSound idSound = eSound::soundDagger;
	if (idWeapon == eType::AXE)
		idSound = eSound::soundAxe;
	else if (idWeapon == eType::BOONGMERANG)
		idSound = eSound::soundBoomerang;
	else if (idWeapon == eType::HOLLYWATTER)
		idSound = eSound::soundHolyWater;
	Sound::GetInstance()->Play(idSound);

	_heart--;
}

Weapon* Simon::GetCurrentWeapon()
{
	Weapon* wp = NULL;
	int idWeapon = CBoard::GetInstance()->GetWeapon();
	if (idWeapon != 0)
		wp = weapons[idWeapon];
	return wp;
};

void Simon::SetState(int state)
{
	//DEBUG -- state = SIMON_STATE_SIT_ATTACK;
	// need update
	//DebugOut(L"[SIMON-SETSTATE] %d\n", state);

	int currentTime = GetTickCount();

	if (attack_start)
		return;

	if (start_jump 
		&& (state != SIMON_STATE_STAND_ATTACK && state != SIMON_STATE_ATTACK_DAGGER)
		)
		return;

	
	switch (state) 
	{
	case SIMON_STATE_ATTACK_DAGGER:
		/*if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();*/
		vx = 0;
		
		if (_heart > 0 && CBoard::GetInstance()->GetWeapon() != 0)
		{
			int idWeapon = CBoard::GetInstance()->GetWeapon();
			if (weapons[idWeapon]->GetState() == DAGGER_STATE_ATTACK)
			{
				state = SIMON_STATE_IDLE;
			}
			
			CAnimations::GetInstance()->Get(SIMON_ANI_STANDING_ATTACKING)->ResetFrame();
			weapons[idWeapon]->SetUsing(true);
		}
		else
		{
			state = SIMON_STATE_IDLE;
		}
		break;

	case SIMON_STATE_STAND_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		Sound::GetInstance()->Play(eSound::soundWhip);
		last_attack = attack_start + ATTACK_TIME;

		VampireKiller::GetInstance()->GetAnimation()->ResetFrame();
		CAnimations::GetInstance()->Get(SIMON_ANI_STANDING_ATTACKING)->ResetFrame();
		break;

	case SIMON_STATE_SIT_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		Sound::GetInstance()->Play(eSound::soundWhip);
		last_attack = attack_start + ATTACK_TIME;
		VampireKiller::GetInstance()->GetAnimation()->ResetFrame();
		CAnimations::GetInstance()->Get(SIMON_ANI_SITTING_ATTACKING)->ResetFrame();
		break;

	case SIMON_STATE_JUMP:
		if (start_jump || currentTime - last_jump < JUMP_WAIT_TIME)
			break;

		start_jump = GetTickCount();
		last_jump = start_jump;
		vy = -SIMON_JUMP_SPEED_Y;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		//vy = 0;
		break;

	case SIMON_STATE_IDLE:
	case SIMON_STATE_IDLE_UP:
	case SIMON_STATE_IDLE_DOWN:
		vx = 0;		
		//vy = 0;
		break;

	case SIMON_STATE_GO_UP:
		nx = StairTrend;
		vx = StairTrend * SIMON_WALKING_SPEED;
		vy = -SIMON_WALKING_SPEED;
		break;

	case SIMON_STATE_GO_DOWN:
		nx = -StairTrend;
		vx = -StairTrend * SIMON_WALKING_SPEED;
		vy = SIMON_WALKING_SPEED;
		break;

	default:
		vx = 0;
		break;
	}

	// update Trend for weapon, weapon trend = simon trend
	weapons[eType::VAMPIREKILLER]->SetTrend(nx);

	this->state = state;
	return;
}


void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int simon_height_pre = this->height;

	height = SIMON_HEIGHT_STAND;
	width = SIMON_WIDTH;
	if (state == SIMON_STATE_DIE)
	{
		width = SIMON_WIDTH_DIE;
		height = SIMON_HEIGHT_DIE;
	}
	else if ( state == SIMON_STATE_SIT_ATTACK
		|| (state == SIMON_STATE_SIT)
		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
	{
		height = SIMON_HEIGHT_SIT;
	}

	//neu dang ngoi chuyen sang dung -> giam y lai de nang simon len keo overlap voi dat de tranh roi xuong
	if (simon_height_pre < this->height)	
		y -= (SIMON_HEIGHT_STAND - SIMON_HEIGHT_SIT);

	CGameObject::GetBoundingBox(left, top, right, bottom);
}