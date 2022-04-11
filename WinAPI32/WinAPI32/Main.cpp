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
	static bool bPressed;

	static POINT start;
	static POINT end;

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

#pragma region Line
	/*case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 100, 20, nullptr);
		LineTo(hdc, 100, 500);
		LineTo(hdc, 400, 330);
		LineTo(hdc, 100, 20);

		MoveToEx(hdc, 500, 20, nullptr);
		LineTo(hdc, 700, 20);
		LineTo(hdc, 500, 400);
		LineTo(hdc, 500, 20);

		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion

#pragma region FreeDraw
	/*case WM_LBUTTONDOWN:
	{
		position.x = LOWORD(lParam);
		position.y = HIWORD(lParam);
		bPressed = true;
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (bPressed == true)
		{
			HDC hdc = GetDC(hwnd);

			MoveToEx(hdc, position.x, position.y, nullptr);

			position.x = LOWORD(lParam);
			position.y = HIWORD(lParam);

			LineTo(hdc, position.x, position.y);
			ReleaseDC(hwnd, hdc);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		bPressed = false;
	}
	break;*/
#pragma endregion

#pragma region Shape
	/*case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		Rectangle(hdc, 100, 100, 500, 500);
		Ellipse(hdc, 100, 100, 500, 500);

		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion

#pragma region DragBox
	/*case WM_LBUTTONDOWN:
	{
		start.x = LOWORD(lParam);
		start.y = HIWORD(lParam);
		bPressed = true;
		
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (bPressed == true)
		{
			end.x = LOWORD(lParam);
			end.y = HIWORD(lParam);
			InvalidateRect(hwnd, nullptr, TRUE);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		bPressed = false;
		
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		Rectangle(hdc, start.x, start.y, end.x, end.y);

		EndPaint(hwnd, &ps);
	}
	break;*/
#pragma endregion

#pragma region Grid
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

		EndPaint(hwnd, &ps);
	}
	break;
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

