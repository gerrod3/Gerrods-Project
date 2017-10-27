#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	WCHAR msc_fontName[] = L"Verdana";
	FLOAT msc_fontSize = 50;

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	width = rect.right;
	height = rect.bottom;

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory));

	res = writeFactory->CreateTextFormat(msc_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, msc_fontSize, L"", &textFormat);

	FLOAT dpiX, dpiY;

	factory->GetDesktopDpi(&dpiX, &dpiY);
	DPIScaleX = dpiX / 96.0f;
	DPIScaleY = dpiY / 96.0f;

	BMPid = -1;
	
	return true;
}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}


void Graphics::DrawUI(std::vector<Ui*>* uis,int bmID){
	for (int i = 0; i < uis->size();i++ ) {
		if (uis->at(i)->checkAlive() && uis->at(i)->checkVisible()) {
			Hitbox h = uis->at(i)->getHitbox();
			TLOHitbox s = uis->at(i)->getSpriteHitbox();
			D2D1_RECT_F dest = { h.cord.x - (h.width / 2),height - (h.cord.y + (h.height / 2)),h.cord.x + (h.width / 2),height - (h.cord.y - (h.height / 2)) };
			D2D1_RECT_F source = { s.left,s.top,s.right,s.bot };
			renderTarget->DrawBitmap(
				Vbmp.at(bmID),		//bitmap
				dest,	//Destination Rectangle
				1.f,	//opacity
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
				source); //Source Rectangle

		}
	}

}


void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {



	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);


}

void Graphics::DrawHealth(float x, float y, float width, float height, float health, float shield, float totalHealth, float totalShield) {

	brush->SetColor(D2D1::ColorF(1.f, 1.f, 1.f, 1.f));
	D2D_RECT_F dest;
	dest.left = x + width / 2.f - 25.f;
	dest.right = x + width / 2.f + 25.f;
	dest.top = y - 20.f;
	dest.bottom = y - 10.f;
	renderTarget->DrawRectangle(dest, brush, 1.0f, NULL);

	float pixelsPerHealth = 48.f / (totalHealth + totalShield);
	float healthPixels = pixelsPerHealth * health;
	D2D_RECT_F rhealth;
	rhealth.left = dest.left + 1.f;
	rhealth.right = rhealth.left + healthPixels;
	rhealth.top = dest.top + 1.f;
	rhealth.bottom = dest.bottom - 1.f;


	//drawing health
	brush->SetColor(D2D1::ColorF(0.f, 1.f, 0.f, 1.f));
	renderTarget->FillRectangle(rhealth, brush);

	float shieldPixels = pixelsPerHealth * shield;
	D2D_RECT_F rshield;
	rshield.left = rhealth.right;
	rshield.right = rshield.left + shieldPixels;
	rshield.top = rhealth.top;
	rshield.bottom = rhealth.bottom;

	//drawing sheilds
	brush->SetColor(D2D1::ColorF(.18f, .79f, 1.f, 1.f));
	renderTarget->FillRectangle(rshield, brush);




}

int Graphics::FindStartX(int ammo) {
	//calculations for the space for finding the number.
	if (ammo <= 10) {
		return (ammo * 11);
	}
	else {
		return (((ammo - 10) * 22) + 110);
	}
}

int Graphics::getDimensions(int a) {
	if (a == 0) return width;
	else if (a == 1) return height;
	else return 0;

}

int Graphics::CreatingBMP(wchar_t* filename) {

	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	//TODO ERROR CHECKING

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);


	renderTarget->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	//spriteWidth = bmp->GetSize().width;
	//spriteHeight = bmp->GetSize().height;
	//spritesAcross = 1;
	//bmpFilenames.push_back(filename);
	BMPid++;
	Vbmp.push_back(bmp);

	return BMPid;
}