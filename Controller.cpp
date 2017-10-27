#include "Controller.h"

State* Controller::currentState;
bool Controller::loading;
Timer* Controller::timer;

void Controller::Init() {

	currentState = 0;
	timer = new Timer();
	
}


void Controller::LoadInitialState(State* lev) {
	lev->loading = true;
	currentState = lev;
	currentState->Load();
	lev->loading = false;
	//currentLevel->tickRate = 64.00;
}

void Controller::SwitchState(State* lev) {
	loading = true;
	currentState->Unload();
	lev->Load();
	delete currentState;
	currentState = lev;
	loading = false;

}

void Controller::Render() {
	if (loading) return;
	currentState->Render();
}

void Controller::Update() {
	/*std::clock_t start;
	double duration = 0;
	start = std::clock();
	currentLevel->Update();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	Sleep(((1.00 / currentLevel->tickRate) - duration) * 1000);*/

	if (loading) return;
	timer->Update();
	currentState->Update(timer->GetTimeTotal(), timer->GetTimeDelta());

}


void Controller::Update(std::vector<IA>* inputQue) {
	if (loading) return;
	timer->Update();
	currentState->Update(timer->GetTimeTotal(), timer->GetTimeDelta(),inputQue);

}

/*void Controller::Update(GameLevel::GameAction action, LPARAM lparam, WPARAM wparam) {
	currentLevel->Update(action, lparam, wparam);
}*/