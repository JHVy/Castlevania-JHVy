#include "Enemy.h"
#include "Sound.h"

void Enemy::Hurt()
{
	Sound::GetInstance()->Play(eSound::soundHurting);
	_energy -= 2;

	if (_energy <= 0)
		this->SetState(CANDLE_STATE_ITEM);
}

