#pragma once

#include "KeyEventHandler.h"
#include "Define.h"
#include "Utils.h"
#include "Simon.h"
#include "CastlevaniaScreen.h"

#define KEYBOARD_BUFFER_SIZE 1024

class CastkeKeyEventHandler : public CKeyEventHandler
{
public:
	CastlevaniaScreen* castleVaninaScreen;

public:
	CastkeKeyEventHandler(CastlevaniaScreen* screen);
	void setCastleScreen(CastlevaniaScreen* screen) {
		this->castleVaninaScreen = screen;
	}

	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

private:
	LPDIRECTINPUT8       di;		// The DirectInput object  
	LPDIRECTINPUTDEVICE8 didv; // The keyboard device
	BYTE  keyStates[256]; // DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	void InitKeyBoard(HWND hWnd);
	void ProcessKeyBoard();
	int IsKeyDown(int KeyCode);
};

