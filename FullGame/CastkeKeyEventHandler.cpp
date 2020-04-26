#include "CastkeKeyEventHandler.h"
#include <dinput.h>
#include "CastlevaniaScreen.h"

CastkeKeyEventHandler::CastkeKeyEventHandler(CastlevaniaScreen* screen, LPDIRECTINPUTDEVICE8 _didv) :CKeyEventHandler()
{
	this->castleVaninaScreen = screen;
	this->didv = _didv;
}

void CastkeKeyEventHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = this->castleVaninaScreen->simon;

	switch (KeyCode)
	{
		case DIK_SPACE:
			break;

		case DIK_DOWN:
			break;

		case DIK_UP:
			if (simon->GetState() == SIMON_STATE_SIT)
				return;
			simon->SetState(SIMON_STATE_GO_UP);
			break;

		default:
			break;
	}
}

void CastkeKeyEventHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	Simon* simon = this->castleVaninaScreen->simon;

	switch (KeyCode)
	{
	/*case DIK_DOWN:
		if (!simon->IsOnStair())
			simon->SetState(SIMON_STATE_UP);
		break;*/

	case DIK_Z:
		if (simon->GetState() == SIMON_STATE_SIT_ATTACK)
		{
			if (IsKeyDown(DIK_DOWN))
				simon->SetState(SIMON_STATE_SIT);
			else
				simon->SetState(SIMON_STATE_UP);
		}
		break;

	}
}

void CastkeKeyEventHandler::KeyState(BYTE* states)
{
	Simon* simon = this->castleVaninaScreen->simon;

	/*if (simon->GetState() == SIMON_STATE_SIT_ATTACK || simon->GetState() == SIMON_STATE_STAND_ATTACK)
		return;
	if (game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_DOWN) && !simon->IsAttacking())
	{
		simon->SetState(SIMON_STATE_SIT_ATTACK);
	}
	else if (game->IsKeyDown(DIK_Z) && game->IsKeyDown(DIK_UP) && !simon->IsAttacking())
	{
		simon->SetState(SIMON_STATE_ATTACK_DAGGER);

	}
	else if (game->IsKeyDown(DIK_UP) && game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT);
	}
	else  if (game->IsKeyDown(DIK_Z))
	{
		if (simon->GetState() == SIMON_STATE_SIT || simon->GetState() == SIMON_STATE_SIT_ATTACK)
			simon->SetState(SIMON_STATE_UP);
		else if ((simon->GetState() == SIMON_STATE_IDLE || simon->GetState() == SIMON_STATE_WALKING_LEFT || simon->GetState() == SIMON_STATE_WALKING_RIGHT) && !simon->IsAttacking())
			simon->SetState(SIMON_STATE_STAND_ATTACK);
	}
	else if (game->IsKeyDown(DIK_X))
	{
		simon->SetState(SIMON_STATE_JUMP);
	}
	else if (game->IsKeyDown(DIK_DOWN) && game->IsKeyDown(DIK_Z) && !simon->IsAttacking())
	{
		simon->SetState(SIMON_STATE_SIT_ATTACK);


	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_GO_DOWN);

	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		simon->SetTrend(1);
		if (simon->IsOnStair()) {
			if (simon->GetStairTrend() == 0)
				simon->SetState(SIMON_STATE_IDLE_UP);
			else
				simon->SetState(SIMON_STATE_IDLE_DOWN);
		}
		else if (!simon->IsAttacking())
		{
			if (simon->GetState() == SIMON_STATE_SIT)
			{
				simon->SetState(SIMON_STATE_UP);
			}
			else
				simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		simon->SetTrend(-1);
		if (simon->IsOnStair()) {
			if (simon->GetStairTrend() != 0)
				simon->SetState(SIMON_STATE_IDLE_UP);
			else
				simon->SetState(SIMON_STATE_IDLE_DOWN);

		}
		else if (!simon->IsAttacking())
		{
			if (simon->GetState() == SIMON_STATE_SIT)
			{
				simon->SetState(SIMON_STATE_UP);
			}
			else
				simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		simon->SetState(SIMON_STATE_GO_UP);
	}
	else if (!game->IsKeyDown(DIK_DOWN) && !game->IsKeyDown(DIK_Z)) {

		if (simon->IsOnStair()) {
			if ((simon->GetStairTrend() == 0 && simon->GetNx() == 1) || (simon->GetStairTrend() == 1 && simon->GetNx() == -1))
				simon->SetState(SIMON_STATE_IDLE_UP);
			else
				simon->SetState(SIMON_STATE_IDLE_DOWN);
		}
		else if (simon->GetState() == SIMON_STATE_SIT || simon->GetState() == SIMON_STATE_SIT_ATTACK)
			simon->SetState(SIMON_STATE_UP);
		else
			simon->SetState(SIMON_STATE_IDLE);
	}*/

}

int CastkeKeyEventHandler::IsKeyDown(int KeyCode) {
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CastkeKeyEventHandler::ProcessKeyBoard() {
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	KeyState((BYTE*)&keyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0) {
			OnKeyDown(KeyCode);
		}
		else
		{
			OnKeyUp(KeyCode);
		}
	}
}
