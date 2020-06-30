#include "Simon.h"
#include "Game.h"
#include "GameConfig.h"

Simon* Simon::_instance = NULL;

Simon* Simon::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Simon();
	}
	return _instance;
}

Simon::Simon() {
	vampireKiller = new VampireKiller();

	untouchable = 0;
	trans_start = 0;
	start_jump = 0;
	width = SIMON_WIDTH;
	height = SIMON_HEIGHT_STAND;

	_energy = 16;
	_score = 0;
	_lives = 3;

	isOnStair = false;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	if (GetTickCount() - start_jump > SIMON_TIME_START_JUMP)
	{
		start_jump = 0;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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
	if (vampireKiller != NULL)
	{
		vampireKiller->y = this->y;
		if (nx < 0)
			vampireKiller->x = this->x - 50;
		else
			vampireKiller->x = this->x - 40;
	}
	vampireKiller->Update(dt, coObjects);


	// simon attack
	if (attack_start) 
	{
		vampireKiller->SetUsing(true);

		int t = GetTickCount();
		if (t - attack_start > ATTACK_TIME) 
		{
			vampireKiller->SetUsing(false);
			attack_start = 0;
			this->state = SIMON_STATE_IDLE;
		}
		return;
	}

	
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
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		id = SIMON_ANI_SITTING_ATTACKING;

		if (vampireKiller != NULL) 
			vampireKiller->Render();
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;

		if (start_jump)
			id = SIMON_ANI_SITTING_ATTACKING;

		if (vampireKiller != NULL) 
			vampireKiller->Render();

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
		//if (start_jump > 0)
			//id = SIMON_ANI_JUMPING;
		//else
			id = SIMON_ANI_IDLE;
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

	//id = SIMON_ANI_IDLE;
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);

	int x1 = x, y1 = y;

	ani->Render(x1, y1, nx, alpha);
	RenderBoundingBox();
}

void Simon::CollisionWithObjects(vector<LPGAMEOBJECT>* coObjects)
{
	if (!coObjects->empty()) 
	{
		Torch* torch;
		CHidenObject* hidenObj;
		Brick* brick;
		Candle* candle;

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
							this->vampireKiller->setUpLevel();
						else if (torch->getItemType() == eType::HEART)
							this->_heart += 5;
						else if (torch->getItemType() == eType::SMALLHEART)
							this->_heart += 2;

						torch->invisibleItem();
						torch->SetState(TORCH_STATE_NOT_EXSIST);
					}
					break;

				case eType::CANDLE:
					candle = (Candle*)obj;
					if (obj->GetState() == CANDLE_STATE_ITEM)
					{
						if (candle->getItemType() == eType::HEART)
							this->_heart += 5;
						else if (candle->getItemType() == eType::SMALLHEART)
							this->_heart++;

						candle->invisibleItem();
						candle->SetState(CANDLE_STATE_NOT_EXSIST);
					}
					break;

				// Va cham cua qua man khac
				case eType::OBJECT_HIDDEN_DOOR:
					GameConfig::GetInstance()->LevelUp();
					break;

				// Va cham STAIR_UP
				case eType::STAIR_UP:
					CollisionWithStair(eType::STAIR_UP, obj);
					break;
					
				// Va cham STAIR_DOWN
				case eType::STAIR_DOWN:
					CollisionWithStair(eType::STAIR_DOWN, obj);
					break;

				default:
					break;
			}
		}
	}
}

void Simon::CollisionWithStair(int type, LPGAMEOBJECT pObj)
{
	isOnStair = true;
	if (type == eType::STAIR_UP)
	{
		DebugOut(L"[SIMON-STAIR_UP] %d\n", isOnStair);
	}
	else if (type == eType::STAIR_DOWN)
	{
		DebugOut(L"[SIMON-STAIR_DOWN] %d\n", isOnStair);
	}
}

void Simon::CollisionWithItems(vector<LPGAMEOBJECT>* coObjects)
{

}



void Simon::SetState(int state)
{
	// need update
	//DebugOut(L"[SIMON-SETSTATE] %d\n", state);

	int currentTime = GetTickCount();

	if (attack_start)
		return;

	if (start_jump && state != SIMON_STATE_STAND_ATTACK) 
		return;


	
	switch (state) 
	{
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;

		//this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_SIT_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;
		//this->vampireKiller->GetAnimation()->ResetFrame();
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
		vy = 0;
		break;

	case SIMON_STATE_IDLE:
		vx = 0;		
		break;

	case SIMON_STATE_GO_UP:
		vx = SIMON_WALKING_SPEED;
		vy = -SIMON_WALKING_SPEED;
		break;

	case SIMON_STATE_GO_DOWN:
		vx = -SIMON_WALKING_SPEED;
		vy = +SIMON_WALKING_SPEED;
		break;

	default:
		vx = 0;
		break;
	}

	
	this->state = state;
	return;
}


//void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	float x1 = x;
//	float y1 = y;
//
//	/*if (nx > 0)
//		x1 = x + 20;
//	else
//		x1 = x - 40;*/
//
//	left = x1;
//	top = y1;
//	right = x1 + SIMON_WIDTH;
//	bottom = y1 + SIMON_HEIGHT_STAND;
//	if (state == SIMON_STATE_DIE)
//	{
//		right = x1 + SIMON_WIDTH_DIE;
//		bottom = y1 + SIMON_HEIGHT_DIE;
//	}
//	else if ( state == SIMON_STATE_SIT_ATTACK
//		|| (state == SIMON_STATE_SIT)
//		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
//	{
//		bottom = y1 + SIMON_HEIGHT_SIT;
//	}
//
//}