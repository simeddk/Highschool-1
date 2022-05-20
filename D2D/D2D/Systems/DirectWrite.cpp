#include "stdafx.h"
#include "DirectWrite.h"

DirectWrite* DirectWrite::instance = nullptr;

IDWriteFactory* DirectWrite::writeFactory = nullptr;
ID2D1DeviceContext* DirectWrite::deviceContext = nullptr;

ID2D1Bitmap1* DirectWrite::bitmap = nullptr;
IDXGISurface* DirectWrite::surface = nullptr;

ID2D1SolidColorBrush* DirectWrite::brush = nullptr;
IDWriteTextFormat* DirectWrite::format = nullptr;

DirectWrite::DirectWrite()
{
	Check(DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&writeFactory
	));

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	IDXGIDevice* dxgiDevice;
	Check(Device->QueryInterface(&dxgiDevice));

	Check(factory->CreateDevice(dxgiDevice, &device));

	Check(device->CreateDeviceContext
	(
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&deviceContext
	));

	CreateBackBuffer();
}

DirectWrite::~DirectWrite()
{
	DeleteBackBuffer();

	SafeRelease(device);
	SafeRelease(deviceContext);
	
	SafeRelease(writeFactory);
	SafeRelease(factory);
}

void DirectWrite::Create()
{
	assert(instance == nullptr);

	instance = new DirectWrite();
}

void DirectWrite::Delete()
{
	SafeDelete(instance);
}

DirectWrite* DirectWrite::Get()
{
	return instance;
}

void DirectWrite::CreateBackBuffer()
{
	SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&surface);

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	Check(deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap));
	deviceContext->SetTarget(bitmap);

	SetFontColor();
	SetFontSize();
}

void DirectWrite::DeleteBackBuffer()
{
	deviceContext->SetTarget(nullptr);

	SafeRelease(brush);
	SafeRelease(format);

	SafeRelease(bitmap);
	SafeRelease(surface);
}

void DirectWrite::RenderText(wstring& text, RECT& rect)
{
	D2D1_RECT_F rt;
	rt.left = (float)rect.left;
	rt.top = (float)rect.top;
	rt.right = (float)rect.right;
	rt.bottom = (float)rect.bottom;

	deviceContext->DrawTextW(text.c_str(), text.length(), format, &rt, brush);
}

void DirectWrite::SetFontSize(UINT size)
{
	SafeRelease(format);

	writeFactory->CreateTextFormat
	(
		L"µ¸¿òÃ¼",
		nullptr,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		(float)size,
		L"ko",
		&format
	);
}

void DirectWrite::SetFontColor(const Color& color)
{
	SafeRelease(brush);

	D2D1::ColorF fontColor(color.r, color.g, color.b, color.a);
	deviceContext->CreateSolidColorBrush(fontColor, &brush);
}
