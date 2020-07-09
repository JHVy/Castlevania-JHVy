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

	// Giam y de ve lui y ve TOP = 0
	cy -= SCREEN_PADING_TOP;

	Simon* simon = Simon::GetInstance();

	// Draw board 
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx, cy);

	// Draw number
	code->DrawNumber(6, cx + 110, cy + 12, simon->GetScore()); // score simon
	code->DrawNumber(4, cx + 295, cy + 12, _time); // time
	code->DrawNumber(2, cx + 465, cy + 12, GameConfig::GetInstance()->CurrentLevel); // state  scene->getScene
	code->DrawNumber(2, cx + 400, cy + 32, simon->GetHeart()); // heart  simon->getHeart - xet va cham simon voi tim, 
	code->DrawNumber(2, cx + 400, cy + 52, simon->GetLives()); // simon->getLives - check sinh menh cua simon

	// Draw energy bar
	code->DrawEnergyBar(cx + 110, cy + 30, 0, simon->GetEnergy()); // player simon->getEnergy - lay gia tri energy cua simon, tru di sau khi va cham voi enemy
	code->DrawEnergyBar(cx + 110, cy + 50, 1, 5); // enemy  boss->getEnergy 

	if (_weapon != 0)
	{

		switch (_weapon)
		{
		case eType::DAGGER:
			sprites->Get(13001)->Draw(cx + 310, cy + 40);;
			break;
		case eType::ITEMAXE:
			sprites->Get(13010)->Draw(cx + 310, cy + 30);
			break;
		case eType::ITEMHOLLYWATTER:
			sprites->Get(13015)->Draw(cx + 310, cy + 27);
			break;
		case eType::ITEMBOONGMERANG:
			sprites->Get(13020)->Draw(cx + 310, cy + 27);
			break;
		default:
			break;
		}
		
		if (_numberOfWeapon != 0)
		{
			if (_numberOfWeapon == 2)
			{
				sprites->Get(13014)->Draw(cx + 440, cy + 40);
			}
			else if (_numberOfWeapon == 3)
			{
				sprites->Get(13017)->Draw(cx + 440, cy + 40);
			}
		}

	}
}

