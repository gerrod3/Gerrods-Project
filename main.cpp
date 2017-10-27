
#include "Graphics.h"
//#include "GameController.h"
#include <thread>
#include <Windowsx.h>
#include <Windows.h>
#include "Controller.h"
#include "TitleScreen.h"

Graphics* graphics;
bool running;
std::vector<IA>* inputQue;

void StopRendering() {
	running = false;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;                       // handle to device context 
	RECT rcClient;                 // client area rectangle 
	POINT ptClientUL;              // client upper left corner 
	POINT ptClientLR;              // client lower right corner 
	static POINTS ptsBegin;        // beginning point 
	static POINTS ptsEnd;          // new endpoint 
	static POINTS ptsPrevEnd;      // previous endpoint 
	static BOOL fPrevLine = FALSE; // previous line flag 



	switch (uMsg) {
	case WM_DESTROY:
		StopRendering();
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		inputQue->push_back({ PRIMARY_CLICK,0 });
		//GameController::Update(GameLevel::GameAction::MOUSE_LCLICK, lParam, wParam);
		return 0;

	case WM_RBUTTONDOWN:
		//GameController::Update(GameLevel::GameAction::MOUSE_RCLICK, lParam, wParam);
		inputQue->push_back({ SECONDARY_CLICK,0 });
		return 0;

	case WM_LBUTTONUP:
		//GameController::Update(GameLevel::GameAction::MOUSE_LRELEASE, lParam, wParam);
		inputQue->push_back({ PRIMARY_RELEASE,0 });
		return 0;

	case WM_RBUTTONUP:
		//GameController::Update(GameLevel::GameAction::MOUSE_RRELEASE, lParam, wParam);
		inputQue->push_back({ SECONDARY_RELEASE,0 });
		return 0;

	case WM_KEYDOWN:
		inputQue->push_back({ KEY_DOWN,0 });
		//GameController::Update(GameLevel::GameAction::KEYBOARD_PRESS, lParam, wParam);
		return 0;

	case WM_KEYUP:
		inputQue->push_back({ KEY_RELEASE,0 });
		//GameController::Update(GameLevel::GameAction::KEYBOARD_RELEASE, lParam, wParam);
		return 0;

	case WM_MOUSEMOVE:
		inputQue->push_back({ MOUSE_MOVE,0 });
		//GameController::Update(GameLevel::GameAction::MOUSE_MOVE, lParam, wParam);
		return 0;
	}




	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void Render(Graphics* g) {
	//TODO add a variable to the while loop

	while (running) {
		Controller::Update(inputQue);
		g->BeginDraw();
		Controller::Render();
		g->EndDraw();
	}

	//delete g;
}


/*void Update() {
	while (running) {
		//GameController::Update();
	}
}*/

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClassEx(&windowclass);
	//HCURSOR cursor1 = LoadCursor(NULL, IDC_ARROW);
	//SetCursor(hCurs3);

	RECT rect = { 0,0,800,600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);


	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Gerrods Program", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!hwnd) { return -1; }

	graphics = new Graphics();

	if (!graphics->Init(hwnd)) {
		delete graphics;
		return -1;
	}
	inputQue = new std::vector<IA>{};
	State::Init(graphics,hwnd);

	ShowWindow(hwnd, nCmdShow);

	Controller::Init();
	Controller::LoadInitialState(new TitleScreen());

	running = true;

	MSG message;
	message.message = WM_NULL;
	//Creates RenderingGraphics thread to render the graphics seperately. 
	std::thread RenderingGraphics(Render, graphics);
	//std::thread UpdateGame(Update);
	while (message.message != WM_QUIT) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&message);
		}
		else {

		}
	}
	//graphics thread rejoins main thread
	RenderingGraphics.join();
	//UpdateGame.join();

	delete graphics;

	return 0;
}


