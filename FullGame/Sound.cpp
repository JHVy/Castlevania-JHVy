
#include "Sound.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::soundWhip, L"Res/sound/usingwhip.wav");
	AddSound(eSound::soundHolyWater, L"Res/sound/holywater.wav");
	AddSound(eSound::soundHit, L"Res/sound/hit.wav");
	AddSound(eSound::soundCollectItem, L"Res/sound/collectitem.wav");
	AddSound(eSound::soundCollectWeapon, L"Res/sound/collectweapon.wav");
	AddSound(eSound::soundHolyCross, L"Res/sound/holycross.wav");
	AddSound(eSound::soundBoomerang, L"Res/sound/08-boomerang.wav");



	AddSound(eSound::soundStopTimer, L"Res/sound/stoptimer.wav");
	AddSound(eSound::soundDagger, L"Res/sound/usingdagger.wav");
	AddSound(eSound::soundDisplayMonney, L"Res/sound/display_monney.wav");
	AddSound(eSound::soundAxe, L"Res/sound/Axe.wav");
	AddSound(eSound::soundStopWatch, L"Res/sound/StopWatch.wav");
	AddSound(eSound::soundInvisibilityPotion_Begin, L"Res/sound/InvisibilityPotion_Begin.wav");
	AddSound(eSound::soundInvisibilityPotion_End, L"Res/sound/InvisibilityPotion_End.wav");


	AddSound(eSound::soundHurting, L"Res/sound/hurting.wav");
	AddSound(eSound::soundOpenDoor, L"Res/sound/opendoor.wav");
	AddSound(eSound::soundBrokenBrick, L"Res/sound/broken_brick.wav");
	AddSound(eSound::soundSplashwater, L"Res/sound/splashwater.wav");
	AddSound(eSound::soundFallingDownWaterSurface, L"Res/sound/fallingdownwatersurface.wav");
	AddSound(eSound::soundGetScoreTimer, L"Res/sound/getscoretime.wav");
	AddSound(eSound::soundGetScoreHeart, L"Res/sound/getscoreheart-[AudioTrimmer.com].wav");



	AddSound(eSound::musicState1, L"Res/music/Stage_01_Vampire_Killer.wav");
	AddSound(eSound::musicLifeLost, L"Res/music/Life_Lost.wav");

	AddSound(eSound::music_Boss, L"Res/music/Boss_Battle_Poison_Mind.wav");
	AddSound(eSound::musicStateClear, L"Res/music/Stage_Clear.wav");
	AddSound(eSound::musicGame_Start_Prologue, L"Res/music/Game_Start_Prologue.wav");
}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound* wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(CGame::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	//dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound* Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}