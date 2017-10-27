#include "TitleScreen.h"
#include "Controller.h"

void TitleScreen::Load() {
	
	spriteSheets = uiTS.initUI();
	uiTS.setBMPid(gfx->CreatingBMP(spriteSheets));
	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	width = gfx->getDimensions(0);
	height = gfx->getDimensions(1);
	//ScreenToClient(hwnd, &mousePosition);

}

void TitleScreen::Unload() {
	
}

void TitleScreen::Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) {
	//deal with input queue
	if (GetCursorPos(&mousePosition)) {
		if (ScreenToClient(hwnd, &mousePosition)) { mPos = {static_cast<float>(mousePosition.x),height - static_cast<float>(mousePosition.y)}; }
			//r = abs(mousePosition.x) / width;
			
	}
	for (int i = 0; i < inputQue->size(); i++) {
		switch (inputQue->at(i).action)
		{
		case PRIMARY_CLICK:
			//r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			//b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			//g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			for (int i = 0; i < uiTS.getSize(); i++) {
				if (Collide::pointCollision(mPos, uiTS.getUI(i)->getHitbox()) && uiTS.getUI(i)->checkClickable()) {
					uiTS.Triggered(i);
				}

			}

			break;
		case SECONDARY_CLICK:
			r = 1.f;
			b = 1.f;
			g = 1.f;
			break;
		default:
			break;
		}
		
	}
	inputQue->clear();
}

void TitleScreen::Update(double timeTotal, double timeDelta) {


}

void TitleScreen::Update(State::GameAction action, LPARAM lparam, WPARAM wparam) {

	//Xpos = GET_X_LPARAM(lparam);
	//Ypos = GET_Y_LPARAM(lparam);

	//sxPos = gfx->PixelsToDipsX(Xpos);
	//syPos = gfx->PixelsToDipsY(Ypos);

}

void TitleScreen::Render() {

	gfx->ClearScreen(r, g, b);
	gfx->DrawUI(uiTS.getUIs(), uiTS.getBMPid());
	
}
