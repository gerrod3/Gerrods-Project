#pragma once
#include "UIClass.h"

class UI_TitleScreen : public UIClass {


public:
	wchar_t* initUI() override;
	void Triggered(int id) override;
};