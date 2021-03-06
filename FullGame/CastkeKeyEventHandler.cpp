#include "CastkeKeyEventHandler.h"
#include <dinput.h>
#include "CastlevaniaScreen.h"
#include "GameConfig.h"

CastkeKeyEventHandler::CastkeKeyEventHandler(CastlevaniaScreen* screen) :CKeyEventHandler()
{
	this->castleVaninaScreen = screen;
}

void CastkeKeyEventHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* simon = this->castleVaninaScreen->simon;

	switch (KeyCode)
	{
		//case DIK_SPACE:
		//	break;

		//case DIK_DOWN:
		//	simon->SetState(SIMON_STATE_SIT);
		//	break;

		//case DIK_UP:
		//	/*if (simon->GetState() == SIMON_STATE_SIT)
		//		return;*/
		//	simon->SetState(SIMON_STATE_GO_UP);
		//	break;

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
	case DIK_DOWN:
			simon->SetState(SIMON_STATE_IDLE);
		break;

	/*case DIK_Z:
		if (simon->GetState() == SIMON_STATE_SIT_ATTACK)
		{
			if (IsKeyDown(DIK_DOWN))
				simon->SetState(SIMON_STATE_SIT);
			else
				simon->SetState(SIMON_STATE_IDLE);
		}
		break;*/

	}
}

void CastkeKeyEventHandler::KeyState(BYTE* states)
{
	// need update
	Simon* simon = Simon::GetInstance();//    this->castleVaninaScreen->simon;

	if (simon->IsAttacking()) {
		return;
	}

	if (IsKeyDown(DIK_Z) && IsKeyDown(DIK_UP) && !simon->IsAttacking())
	{
		simon->SetState(SIMON_STATE_ATTACK_DAGGER);
		return;
	}

	if (IsKeyDown(DIK_Z)) {
		DebugOut(L"Z - Key Down");
		if (simon->isOnStair)
			return;

		if (!simon->IsSitting())
			simon->SetState(SIMON_STATE_STAND_ATTACK);
		else
			simon->SetState(SIMON_STATE_SIT_ATTACK);

		return;
	}

	if (IsKeyDown(DIK_X))
	{
		if(simon->IsSitting() || simon->isOnStair)
			return;
		DebugOut(L" X - Key Down");
		simon->SetState(SIMON_STATE_JUMP);
		//return;	//vi cai nay nen moi luc no chi nhan duoc 1 button thoi, neu muon nhan dong thoi nhieu button th� ko return
	}

	if (IsKeyDown(DIK_LEFT))
	{
		if (simon->isOnStair)
			return;

		if (!simon->IsAttacking())
		{
			if (simon->GetState() == SIMON_STATE_SIT)
			{
				simon->SetState(SIMON_STATE_UP);
			}
			else
				simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
		return;
	}

	if (IsKeyDown(DIK_RIGHT)) {
		//simon->SetTrend(1);
		if (simon->isOnStair)
			return;

		if (!simon->IsAttacking())
		{
			if (simon->GetState() == SIMON_STATE_SIT)
			{
				simon->SetState(SIMON_STATE_UP);
			}
			else
				simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		return;
	}

	if (IsKeyDown(DIK_DOWN))
	{
		simon->CheckCollisionWithStair(DIK_DOWN);
		if (simon->isOnStair)
			return;


		if (simon->IsAttacking()) {
			simon->SetState(SIMON_STATE_SIT_ATTACK);
		}
		else {
			simon->SetState(SIMON_STATE_SIT);
		}

		return;
	}

	if (IsKeyDown(DIK_UP))
	{
		if (simon->IsSitting())
			simon->SetState(SIMON_STATE_IDLE);

		simon->CheckCollisionWithStair(DIK_UP);

		return;
	}

	// HACK LEVEL
	for (int i = DIK_1; i <= DIK_6; i++)
	{
		if (IsKeyDown(i))
		{
			int gameLevel = i - DIK_ESCAPE;
			GameConfig::GetInstance()->SetGameLevel(gameLevel);
			return;
		}
	}

	if (IsKeyDown(DIK_0))
	{
		simon->HackSimon();
		return;
	}



	//default
	if (simon->isOnStair) 
	{
		if ((simon->StairTrend == 1 && simon->GetTrend() == 1)
			|| (simon->StairTrend != 1 && simon->GetTrend() != 1))
			simon->SetState(SIMON_STATE_IDLE_UP);
		else
			simon->SetState(SIMON_STATE_IDLE_DOWN);
	}
	else
	{
		simon->SetState(SIMON_STATE_IDLE);
	}
	
	return;
}

int CastkeKeyEventHandler::IsKeyDown(int KeyCode) {
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CastkeKeyEventHandler::InitKeyBoard(HWND hWnd) {
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");

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
