#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define RECT_INIT(x, y, s) { (x - s / 2), (y - s / 2), (x + s / 2), (y + s / 2) }
#define RECT_RENDER(rect) Rectangle(Hdc, rect.left, rect.top, rect.right, rect.bottom);

const wstring Title = L"WinAPI32";

extern HDC Hdc;
extern HWND Hwnd;