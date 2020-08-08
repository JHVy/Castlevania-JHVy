#include "Enemy.h"
#include "Sound.h"

void Enemy::Hurt()
{
	Sound::GetInstance()->Play(eSound::soundHurting);
	_energy -= 2;

	if (_energy <= 0)	//dead
	{	
		this->SetState(CANDLE_STATE_ITEM);
		this->item->SetPosition(this->x, this->y);
	}
}

