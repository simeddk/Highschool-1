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

	switch (message)
	{
#pragma region MessageBox
	/*case WM_LBUTTONUP:
	{
		int result = MessageBox(hwnd, L"방가의 메세지", L"방가의 캡션", MB_OK);

		if (result == IDOK)
			PostQuitMessage(0);
	}
	break;*/
#pragma endregion

#pragma region Paint
	/*case WM_LBUTTONDOWN:
	{
		wstring str = L"마우스가 눌림!!";

		HDC hdc = GetDC(hwnd);
		TextOut(hdc, 200, 200, str.c_str(), str.length());
		ReleaseDC(hwnd, hdc);
	}
	break;

	case WM_PAINT:
	{
		wstring str = L"WM_PAINT 메세지 발생";

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 200, 400, str.c_str(), str.length());
		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion

#pragma region KeyEvent
	/*case WM_KEYDOWN:
	{
		if (wParam == VK_UP)
			y -= 10;
		else if (wParam == VK_DOWN)
			y += 10;

		if (wParam == VK_LEFT)
			x -= 10;
		else if (wParam == VK_RIGHT)
			x += 10;
			
		InvalidateRect(hwnd, nullptr, TRUE);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, x, y, L"★", 1);
		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion

#pragma region MousePosition
	/*case WM_MOUSEMOVE:
	{
		position.x = LOWORD(lParam);
		position.y = HIWORD(lParam);
		InvalidateRect(hwnd, nullptr, TRUE);
	}
	break;

	case WM_PAINT:
	{
		wstring str = to_wstring(position.x);
		str += L", ";
		str += to_wstring(position.y);

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, position.x, position.y, str.c_str(), str.length());
		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion


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

