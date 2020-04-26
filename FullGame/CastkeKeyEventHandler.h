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
	CastkeKeyEventHandler(CastlevaniaScreen* screen, LPDIRECTINPUTDEVICE8 _didv);
	void setCastleScreen(CastlevaniaScreen* screen) {
		this->castleVaninaScreen = screen;
	}

	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

private:
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256]; // DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	void ProcessKeyBoard();
	int IsKeyDown(int KeyCode);
};

