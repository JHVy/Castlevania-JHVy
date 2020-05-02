#pragma once

#include "Define.h"
#include "Utils.h"

class Camera
{
private:
	float screen_x, screen_y;
	float mainObject_x, mainObject_y;

public:
	float position_x, position_y;

public:
	Camera(float _screen_x, float _screen_y) {
		this->screen_x = _screen_x;
		this->screen_y = _screen_y;
	}

	Camera(float _screen_x, float _screen_y, float _mainObject_x, float _mainObject_y) {
		this->screen_x = _screen_x;
		this->screen_y = _screen_y;
		this->mainObject_x = _mainObject_x;
		this->mainObject_y = _mainObject_y;
	}

	Camera(){
		this->screen_x = 0;
		this->screen_y = 0;
		this->mainObject_x = 0;
		this->mainObject_y = 0;
	}

public:
	void getPosition(float& resx, float& resy) {
		calPosition();

		resx = this->position_x;
		resy = this->position_y;
	}

	void setScreenSize(float _screen_x, float _screen_y) {
		this->screen_x = _screen_x;
		this->screen_y = _screen_y;
		
		calPosition();
	}

	void setMainObjectPosition(float _center_x, float _center_y) {
		this->mainObject_x = _center_x;
		this->mainObject_y = _center_y;

		calPosition();
	}

private:
	void calPosition() {
		float cam_x = 0, cam_y = 0;

		float kc_x = SCREEN_WIDTH / 2;
		float kc_y = SCREEN_HEIGHT / 2;

		cam_x = mainObject_x - kc_x;
		//cam_y = mainObject_y - kc_y;

		if (cam_x + SCREEN_WIDTH > this->screen_x)
			cam_x = this->screen_x - SCREEN_WIDTH;
		if (cam_x < 0) cam_x = 0;

		DebugOut(L"[DEBUG] Cal postion camera : (%f, %f) - (%f, %f) - (%f, %f) !\n", screen_x, screen_y, mainObject_x, mainObject_y, cam_x, cam_y);
		
		if (cam_y < 0) cam_y = 0;

		this->position_x = cam_x;
		this->position_y = cam_y;
	}
};

