#include "CBoard.h"
#include "GameConfig.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{
	if (GetTickCount() - _count >= 1000)  // 1000 millisecond
	{
		_time--;
		_count = GetTickCount();
	}
}
void CBoard::Render()
{

	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);

	Simon* simon = Simon::GetInstance();

	// Draw board 
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx + 540, cy);

	// Draw number
	code->DrawNumber(6, cx + 110, cy + 12, simon->GetScore()); // score simon
	code->DrawNumber(4, cx + 295, cy + 12, _time); // time
	code->DrawNumber(2, cx + 465, cy + 12, GameConfig::GameLevel); // state  scene->getScene
	code->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart()); // heart  simon->getHeart - xet va cham simon voi tim, 
	code->DrawNumber(2, cx + 400, cy + 52, simon->GetLives()); // simon->getLives - check sinh menh cua simon

	// Draw energy bar
	code->DrawEnergyBar(cx + 110, cy + 30, 0, simon->GetEnergy()); // player simon->getEnergy - lay gia tri energy cua simon, tru di sau khi va cham voi enemy
	code->DrawEnergyBar(cx + 110, cy + 50, 1, 5); // enemy  boss->getEnergy 

}