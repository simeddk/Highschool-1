#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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
	static RECT player;
	static POINT position = { WINDOWWIDTH / 2,  WINDOWHEIGHT - 65 };
	static LONG movespeed = 20;

	static int delay = 50;

	struct DropRect
	{
		RECT rect;
		LONG dropSpeed;
	};

	static vector<DropRect> dropRects;

	static int score = 0;
	static int level = 1;

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hwnd, 1, 10, nullptr);
		srand((UINT)time(nullptr));
	}
	break;

	case WM_TIMER:
	{
		InvalidateRect(hwnd, nullptr, TRUE);

		//Player의 left, top, right, bottom을 정의한 부분
		player = RECT_INIT(position.x, position.y, 50);

		//delay가 50이상 경우 똥 생성
		if (delay >= 50)
		{
			DropRect dropRect;
			dropRect.rect.left = rand() % WINDOWWIDTH;
			dropRect.rect.right = dropRect.rect.left + 25;
			dropRect.rect.top = -25;
			dropRect.rect.bottom = 0;

			dropRect.dropSpeed = rand() % 10 + 5;

			dropRects.push_back(dropRect);

			delay = rand() % 50;
		}
		//delay가 50보다 작은 경우 delay를 level만큼 증가
		else
			delay += level;

		//똥 관련 반복문
		vector<DropRect>::iterator it;
		for (it = dropRects.begin(); it != dropRects.end(); ++it)
		{
			//똥 낙하
			it->rect.top += it->dropSpeed;
			it->rect.bottom += it->dropSpeed;

			//점수 올리기
			/*if (it->rect.top > WINDOWHEIGHT)
			{
				score++;
				dropRects.erase(it);
			}*/

			
		}

	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'A': case VK_LEFT:
		{
			position.x -= (position.x - 12 >= 0) ? movespeed : 0;
		}
		break;

		case 'D': case VK_RIGHT:
		{
			position.x += (position.x <= WINDOWWIDTH - 25) ? movespeed : 0;
		}
		break;
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT_RENDER(player);

		for (UINT i = 0; i < dropRects.size(); i++)
			RECT_RENDER(dropRects[i].rect);

		EndPaint(hwnd, &ps);
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
