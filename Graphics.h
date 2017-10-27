#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <wincodec.h>
#include "Ui.h"
//typedef D2D_RECT_F Hitbox;

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	IDWriteTextFormat* textFormat;
	IDWriteFactory* writeFactory;
	static const WCHAR msc_fontName[];
	static const FLOAT msc_fontSize;
	float DPIScaleX = 1.0f;
	float DPIScaleY = 1.0f;
	int width;
	int height;
	

	//stuff for bitmaps
	ID2D1Bitmap* bmp;
	std::vector<ID2D1Bitmap*> Vbmp;
	int spriteWidth, spriteHeight;
	int spritesAcross;
	int BMPid;

public:

	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() {
		return renderTarget;
	}

	int CreatingBMP(wchar_t* filename);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	//good drawing commmands
	void DrawUI(std::vector<Ui*>* uis,int bmID);

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawHealth(float x, float y, float width, float height, float health, float shield, float totalHealth, float totalShield);
	int FindStartX(int ammo);
	
	int getDimensions(int x);
	template<typename T>
	float PixelsToDipsX(T x) {
		return static_cast<float>(x) / DPIScaleX;
	}
	template<typename T>
	float PixelsToDipsY(T y) {
		return static_cast<float>(y) / DPIScaleY;
	}

	
};