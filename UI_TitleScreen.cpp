#include "UI_TitleScreen.h"


	
	

	

wchar_t*	UI_TitleScreen::initUI() {
		spriteName = L"TitleScreen.png";
		/*Hitbox gbHB = { {100,100},100,100,SHAPE::SQAURE };
		TLOHitbox gbSHB = { 0,0,100,100 };
		Ui *greenbox = new Ui(L"greenbutton", gbHB, gbSHB, 0);
		
		
		Hitbox bbHB = { {200,100 }, 100, 100,SHAPE::SQAURE };
		TLOHitbox bbSHB = { 100,0,200,100 };
		Ui *bluebox = new Ui(L"bluebox", bbHB, bbSHB, 1);

		greenbox->addChild(1);

		puis->push_back(greenbox);
		puis->push_back(bluebox);*/

		//ok lets make a real titlescreen ui
		//will have three main buttons, play, settings and quit
		//one main container will contain play and settings
		//when play and settings is hit, will change to their containers that have their respective buttons

		Ui *mainContain = new Ui(L"mainContainer", hbZero, hbtlZero, 0);
		Ui *playContain = new Ui(L"playContainer", hbZero, hbtlZero, 1);
		Ui *settingContain = new Ui(L"settingContainer", hbZero, hbtlZero, 2);

		Hitbox playHB = { {150,400},200,100 ,SHAPE::SQAURE};
		TLOHitbox playSHB = { 0,0,200,100 };
		Ui* play = new Ui(L"play", playHB, playSHB, 3);

		Hitbox settingHB = { {150,300},200,100,SHAPE::SQAURE };
		TLOHitbox settingSHB = { 200,0,400,100 };
		Ui* setting = new Ui(L"setting", settingHB, settingSHB, 4);

		Hitbox backHB = { {150,50},25,25,SHAPE::SQAURE };
		TLOHitbox backSHB = { 400,0,425,25 };
		Ui* back = new Ui(L"back", backHB, backSHB, 9);

		Hitbox generalHB = { {150,500},150,50,SHAPE::SQAURE };
		TLOHitbox generalSHB{ 0,100,150,150 };
		Ui* general = new Ui(L"general", generalHB, generalSHB, 5);

		Hitbox controlHB = { { 300,500 },150,50,SHAPE::SQAURE };
		TLOHitbox controlSHB{ 150,100,300,150 };
		Ui* control = new Ui(L"control", controlHB, controlSHB, 6);

		Hitbox videoHB = { { 450,500 },150,50,SHAPE::SQAURE };
		TLOHitbox videoSHB{ 300,100,450,150 };
		Ui* video = new Ui(L"video", videoHB, videoSHB, 7);

		Hitbox audioHB = { { 600,500 },150,50,SHAPE::SQAURE };
		TLOHitbox audioSHB{ 450,100,600,150 };
		Ui* audio = new Ui(L"audio", audioHB, audioSHB, 8);

		std::vector<int> mainCilds = { 3,4 };
		mainContain->setChilds(&mainCilds);
		std::vector<int> settingCHilds = {9, 5,6,7,8 };
		settingContain->setChilds(&settingCHilds);
		
		
		play->setClickable(true);
		setting->setClickable(true);
		back->setClickable(true);

		puis->push_back(mainContain);
		puis->push_back(playContain);
		puis->push_back(settingContain);
		puis->push_back(play);
		puis->push_back(setting);
		puis->push_back(general);
		puis->push_back(control);
		puis->push_back(video);
		puis->push_back(audio);
		puis->push_back(back);
		prevState.resize(puis->size());

		toggleChildren(2);
		programMasters();
		updateState();
		return spriteName;
	}
	
void UI_TitleScreen::Triggered(int id) {

	switch (id)
	{
	case 9:
		setState(-1);
		break;
	case 0: {
		toggleChildren(id);
		break;
	}
	case 1:
		break;


	case 4:
		updateState();
		puis->at(0)->setAlive(false);
		toggleChildren(2);
		confirmAlive();
		
		break;
	default:
		break;
	}

	//updateState();
}


