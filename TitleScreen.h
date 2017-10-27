#pragma once
#include "State.h"
#include "UI_TitleScreen.h"
#include "Collide.h"

class TitleScreen : public State {

	UI_TitleScreen uiTS;
	//will make this into a vector
	wchar_t* spriteSheets;
	float r, g, b;
	float width, height;
	POINT mousePosition;
	Point mPos;


public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(State::GameAction action, LPARAM lparam, WPARAM wparam) override;
	void Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) override;
};