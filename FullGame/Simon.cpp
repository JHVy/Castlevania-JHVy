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

	_energy = 16;
	_score = 0;
	_lives = 3;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// collision weapon
	if (!coObjects->empty() && IsAttacking()) {
		RECT rect, rect1, rectSimon;

		// weapon vs item
		float l = 0, t = 0, r = 0, b = 0;
		if (vampireKiller)
			this->vampireKiller->GetBoundingBox(l, t, r, b);


		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;
		
		for (int index = 0; index < coObjects->size(); index++) {
			LPGAMEOBJECT obj = coObjects->at(index);

			if (obj->_type != eType::TORCH)
				continue;
			
			float l1, t1, r1, b1;
			obj->GetBoundingBox(l1, t1, r1, b1);
			
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;

			if (CGame::GetInstance()->isCollision(rect, rect1)) {
				obj->SetState(TORCH_STATE_ITEM);
			}
		}
	}

	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

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
		float min_tx, min_ty, nx = 0, ny;

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
	//CollisionWithObjects(coObjects);

	// simon attack
	if (attack_start) 
	{
		int t = GetTickCount();
		if (t - attack_start > ATTACK_TIME) 
		{
			attack_start = 0;
			this->state = SIMON_STATE_IDLE;
			return;
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

		if (vampireKiller != NULL) {
			vampireKiller->Render(x, y, state, nx);
			vampireKiller->SetPosition(x, y, state, nx);
		}
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;

		if (start_jump)
			id = SIMON_ANI_SITTING_ATTACKING;

		if (vampireKiller != NULL) {
			vampireKiller->Render(x, y, state, nx);
			vampireKiller->SetPosition(x, y, state, nx);
		}

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
		if (start_jump > 0)
			id = SIMON_ANI_JUMPING;
		else
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
	DebugOut(L"[START DRAW SIMON] ");
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);

	int x1 = x + SCREEN_PADING_TOP, y1 = y + SCREEN_PADING_TOP;

	ani->Render(x1, y1, nx, alpha);
}

void Simon::CollisionWithObjects(vector<LPGAMEOBJECT>* coObjects)
{
	if (!coObjects->empty()) 
	{
		RECT rect1, rectSimon;

		// simon vs item
		float ls = 0, ts = 0, rs = 0, bs = 0;
		this->GetBoundingBox(ls, ts, rs, bs);

		rectSimon.left = (int)ls;
		rectSimon.top = (int)ts;
		rectSimon.right = (int)rs;
		rectSimon.bottom = (int)bs;
		float l1 = 0, t1 = 0, r1 = 0, b1 = 0;
		Torch* torch;
		CHidenObject* hidenObj;
		Brick* brick;
		Candle* candle;

		//duyet qua list object de check va cham va xu ly
		for (int index = 0; index < coObjects->size(); index++)
		{
			LPGAMEOBJECT obj = coObjects->at(index);

			switch (obj->_type)
			{
			case eType::TORCH:
				torch = (Torch*)(obj);

				obj->GetBoundingBox(l1, t1, r1, b1);

				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;

				if (CGame::GetInstance()->isCollision(rect1, rectSimon)) 
				{
					if (torch->GetState() == TORCH_STATE_ITEM) 
					{
						if (torch->getItemType() == eType::WHIPUPGRADE)
							this->vampireKiller->setUpLevel();
						else if (torch->getItemType() == eType::HEART)
							this->_heart += 5;
						else if (torch->getItemType() == eType::SMALLHEART)
							this->_heart++;

						torch->invisibleItem();
						torch->SetState(TORCH_STATE_NOT_EXSIST);
					}
				}
			case eType::CANDLE:
				candle = (Candle*)(obj);

				obj->GetBoundingBox(l1, t1, r1, b1);

				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;

				if (CGame::GetInstance()->isCollision(rect1, rectSimon))
				{
					if (candle->GetState() == CANDLE_STATE_ITEM)
					{
						if (candle->getItemType() == eType::HEART)
							this->_heart += 5;
						else if (candle->getItemType() == eType::SMALLHEART)
							this->_heart++;

						candle->invisibleItem();
						candle->SetState(CANDLE_STATE_NOT_EXSIST);
					}
				}
				break;


			// Va cham cua qua man khac
			case eType::OBJECT_HIDDEN_DOOR:
				hidenObj = (CHidenObject*)(obj);

				obj->GetBoundingBox(l1, t1, r1, b1);

				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;

				//Va cham DOOR
				if (CGame::GetInstance()->isCollision(rect1, rectSimon)) {
					GameConfig::GetInstance()->LevelUp();
				}
				break;

			// check va cham gach
			case eType::BRICK_2:
				brick = (Brick*)(obj);

				obj->GetBoundingBox(l1, t1, r1, b1);

				rect1.left = (int)l1;
				rect1.top = (int)t1;
				rect1.right = (int)r1;
				rect1.bottom = (int)b1;
				
				// Simon cham vat can (brick)
				if (vy > 0	//dang roi xuong
					&& (rectSimon.bottom + vy) >= rect1.top 

					&& (Utils::IsOverlapX(rectSimon, rect1))
					)	
				{
					vy = 0;
					start_jump = 0;
				}

				if (vx > 0	//go right
					&& (rectSimon.right + vx) >= rect1.left
					&& (Utils::IsOverlapY(rectSimon, rect1))
					)
				{
					//vx = 0;
				}

				//if (vx < 0	//go left
				//	&& (rectSimon.left + vx) <= rect1.right
				//	&& (Utils::IsOverlapY(rect1, rectSimon))
				//	)
				//{
				//	vx = 0;
				//}
				
				break;

			default:
				break;
			}
		}
	}
}

void Simon::CollisionWithHidenBricks(vector<LPGAMEOBJECT>* coObjects)
{

}

void Simon::CollisionWithItems(vector<LPGAMEOBJECT>* coObjects)
{

}



void Simon::SetState(int state)
{
	// need update
	DebugOut(L"[SIMON-SETSTATE] %d\n", state);

	int currentTime = GetTickCount();

	if (attack_start)
		return;

	if (start_jump && state != SIMON_STATE_STAND_ATTACK) 
		return;


	
	switch (state) {
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;

		this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_SIT_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;
		this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_JUMP:
		if (start_jump || currentTime - last_jump < JUMP_WAIT_TIME)
			break;

		start_jump = GetTickCount();
		last_jump = start_jump;
		vy = -SIMON_JUMP_SPEED_Y;
		//y = SIMON_POS_Y;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		vy = 0;
		//y = SIMON_POS_Y;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		//vy = 0;
		//y = SIMON_POS_Y;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		break;

	case SIMON_STATE_IDLE:
		vx = 0;		
		break;

	default:
		vx = 0;
		break;
	}

	this->state = state;

	return;
}


void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float x1 = x;
	float y1 = y;

	/*if (nx > 0)
		x1 = x + 20;
	else
		x1 = x - 40;*/

	left = x1;
	top = y1;
	right = x1 + SIMON_WIDTH;
	bottom = y1 + SIMON_HEIGHT_STAND;
	if (state == SIMON_STATE_DIE)
	{
		right = x1 + SIMON_WIDTH_DIE;
		bottom = y1 + SIMON_HEIGHT_DIE;
	}
	else if ( state == SIMON_STATE_SIT_ATTACK
		|| (state == SIMON_STATE_SIT)
		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
	{
		bottom = y1 + SIMON_HEIGHT_SIT;
	}

}