#pragma once
#include "Timer.h"
#include "State.h"

class Controller {

	Controller() {}
	static State* currentState;
	

	static Timer* timer;

public:
	static bool loading;

	static void Init();

	static void LoadInitialState(State* lev);
	static void SwitchState(State* lev);

	static void Render();
	static void Update();
	static void Update(std::vector<IA>* inputQue);
//	static void Update(GameLevel::GameAction action, LPARAM lparam, WPARAM wparam);
};