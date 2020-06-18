#include "Simon.h"
#include "Game.h"
#include "GameConfig.h"

//Simon* Simon::_instance = NULL;
//
//Simon* Simon::GetInstance()
//{
//	if (_instance == NULL)
//	{
//		_instance = new Simon();
//	}
//	return _instance;
//}

Simon* Simon::_instance = NULL;
//int Simon::_heart = 0;

Simon* Simon::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Simon();
	}

	return _instance;
}

Simon::Simon() {
	VampireKiller* rob = new VampireKiller();
	vampireKiller = rob;
	//vampireKiller->setUpLevel();
	//vampireKiller->setUpLevel();

	untouchable = 0;
	trans_start = 0;
	start_jump = 0;

	_energy = 16;
	_score = 0;
	_lives = 3;
	_heart = 0;
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

	// collision simon with object item
	if (!coObjects->empty()) {
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

					if (CGame::GetInstance()->isCollision(rect1, rectSimon)) {
						if (torch->GetState() == TORCH_STATE_ITEM) {

							//

							if (torch->getItemType() == eType::WHIPUPGRADE)
								this->vampireKiller->setUpLevel();
							else if (torch->getItemType() == eType::HEART)
								_heart+=5;

							torch->invisibleItem();
							torch->SetState(TORCH_STATE_NOT_EXSIST);
						}
					}
					break;

				case eType::OBJECT_HIDDEN_DOOR:
					hidenObj = (CHidenObject*)(obj);

					obj->GetBoundingBox(l1, t1, r1, b1);

					rect1.left = (int)l1;
					rect1.top = (int)t1;
					rect1.right = (int)r1;
					rect1.bottom = (int)b1;

					//Va cham DOOR
					if (CGame::GetInstance()->isCollision(rect1, rectSimon)) {
						++GameConfig::GameLevel;
					}
					break;

				default:
					break;
			}
		}
	}

	// update simon location
	x = x + vx * dt;
	y = y + vy * dt;
	vy += SIMON_GRAVITY * dt;

	if (x < 30) x = 30;

	if (y > SIMON_POS_Y) {
		y = SIMON_POS_Y;
		vy = 0;
		vx = 0;
		start_jump = 0;
	}

	// simon attack
	if (attack_start) {
		int t = GetTickCount();

		if (t - attack_start > ATTACK_TIME) {
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


	DebugOut(L"[START DRAW SIMON] ");
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);

	int x1 = x, y1 = y;
	if (id == SIMON_ANI_SITTING || id == SIMON_ANI_SITTING_ATTACKING)
		y1 = y1 + 15;
	ani->Render(x1, y1, nx, alpha);

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
		y = SIMON_POS_Y;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		vy = 0;
		y = SIMON_POS_Y;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		vy = 0;
		y = SIMON_POS_Y;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}

	this->state = state;

	return;
}


void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	float x1 = x;
	float y1 = y;

	if (nx > 0)
		x1 = x + 20;
	else
		x1 = x - 40;

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