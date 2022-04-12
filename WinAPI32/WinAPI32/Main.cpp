#include "stdafx.h"
#include "Game/Game.h"

HDC Hdc = nullptr;
HWND Hwnd = nullptr;

Game* game = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	game = new Game();

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = Title.c_str();
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int centerX = screenX / 2 - WINDOWWIDTH / 2;
	int centerY = screenY / 2 - WINDOWHEIGHT / 2;

	HWND hwnd = CreateWindow
	(
		Title.c_str(),
		Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		centerX,
		centerY,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	Hwnd = hwnd;

	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Update();
			//Render();
		}
	}

	DestroyWindow(hwnd);
	UnregisterClass(Title.c_str(), hInstance);

	delete game;
	game = nullptr;

	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hwnd, 1, 10, nullptr);
	}
	break;

	case WM_TIMER:
	{
		game->Update();
	}
	break;

	case WM_PAINT:
	{
		game->Render();
	}
	break;


	case WM_CLOSE: case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
