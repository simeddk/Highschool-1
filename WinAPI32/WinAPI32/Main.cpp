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
	static POINT position1 = { 100, 100 };
	static POINT position2 = { 200, 200 };

	static RECT rect1;
	static RECT rect2;
	UINT moveSpeed = 20;

	enum class EDirctionType { None, Left, Right, Up, Down };
	static EDirctionType type;


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

		rect1.left = position1.x - 25;
		rect1.top = position1.y - 25;
		rect1.right = position1.x + 25;
		rect1.bottom = position1.y + 25;

		rect2.left = position2.x - 50;
		rect2.top = position2.y - 50;
		rect2.right = position2.x + 50;
		rect2.bottom = position2.y + 50;

		RECT temp;
		if (IntersectRect(&temp, &rect1, &rect2) == TRUE)
		{
			switch (type)
			{
				case EDirctionType::Left:	position2.x -= moveSpeed;	break;
				case EDirctionType::Right:	position2.x += moveSpeed;	break;
				case EDirctionType::Up:		position2.y -= moveSpeed;	break;
				case EDirctionType::Down:	position2.y += moveSpeed;	break;
			}
		}
			
	}
	break;

	case WM_KEYDOWN:
	{
		if (wParam == 'A' || wParam == VK_LEFT)
		{
			position1.x -= moveSpeed;
			type = EDirctionType::Left;
		}
		else if (wParam == 'D' || wParam == VK_RIGHT)
		{
			position1.x += moveSpeed;
			type = EDirctionType::Right;
		}

		if (wParam == 'W' || wParam == VK_UP)
		{
			position1.y -= moveSpeed;
			type = EDirctionType::Up;
		}
		else if (wParam == 'S' || wParam == VK_DOWN)
		{
			position1.y += moveSpeed;
			type = EDirctionType::Down;
		}

	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
		Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);
		
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

