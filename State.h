#pragma once
#include "Graphics.h"
class State {
protected:
	static Graphics* gfx;
	 static HWND hwnd;
	double sec = 1.00;


public:
	enum GameAction {
		MOUSE_LCLICK,
		MOUSE_RCLICK,
		MOUSE_LRELEASE,
		MOUSE_RRELEASE,
		MOUSE_DRAG,
		KEYBOARD_PRESS,
		KEYBOARD_RELEASE,
		SYS_KEYBOARD_PRESS,
		MOUSE_MOVE
	};
	static void Init(Graphics* graphics,HWND hw) {
		gfx = graphics;
		hwnd = hw;
	}
	//clock_t FPSsec; 
	//int FPS;
	//int oldFPS;
	//bool error = false;
	//double tickRate;
	bool loading;
	float Xpos, Ypos, syPos, sxPos;
	bool RightKeyDown;
	bool LeftKeyDown;
	bool UpKeyDown;
	bool DownKeyDown;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Update(GameAction action, LPARAM lparam, WPARAM wparam) = 0;
	virtual void Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) = 0;
};