#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = Title.c_str();
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	HWND hwnd = CreateWindow
	(
		Title.c_str(),
		Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		100,
		20,
		WINDOWWIDTH,
		WINDOWHEIGHT,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

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

	return msg.wParam;
	
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT position;
	static int count;

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hwnd, 1, 100, nullptr);
	}
	break;

	case WM_TIMER:
	{
		InvalidateRect(hwnd, nullptr, TRUE);
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case 'W': case VK_UP:
			{
				position.y -= (position.y > 0) ? 1 : 0;
			}
			break;

			case 'S': case VK_DOWN:
			{
				position.y += (position.y < 8) ? 1 : 0;
			}
			break;

			case 'D': case VK_RIGHT:
			{
				position.x += (position.x < 15) ? 1 : 0;
			}
			break;

			case 'A': case VK_LEFT:
			{
				position.x -= (position.x > 0) ? 1 : 0;
			}
			break;
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		int massSize = WINDOWHEIGHT / 9;

		for (int i = 0; i < 9; i++)
		{
			MoveToEx(hdc, 0, i * massSize, nullptr);
			LineTo(hdc, WINDOWWIDTH, i * massSize);
		}

		for (int i = 0; i < 16; i++)
		{
			MoveToEx(hdc, i * massSize, 0, nullptr);
			LineTo(hdc, i * massSize, WINDOWHEIGHT);
		}

		int moveX = massSize * position.x;
		int moveY = massSize * position.y;

		Rectangle
		(
			hdc,
			moveX + 10,					//Left
			moveY + 10,					//Top
			moveX + massSize - 10,		//Right
			moveY + massSize - 10		//Bottom
		);

		wstring text = L"";
		text += to_wstring(position.x);
		text += L", ";
		text += to_wstring(position.y);

		TextOut
		(
			hdc,
			moveX + massSize * 0.5f,
			moveY + massSize * 0.5f,
			text.c_str(),
			text.size()
		);

		EndPaint(hwnd, &ps);
	}
	break;


	case WM_CLOSE : case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

