#include "stdafx.h"
#include "Game.h"
#include "Objects/Player.h"
#include "Objects/Bullet.h"

Game::Game()
	: score(0)
	, level(1)
	, cursorPosition({0, 0})
{
	srand((UINT)time(nullptr));

	player = new Player();
	bullet = new Bullet();
}

Game::~Game()
{
	delete player;
	player = nullptr;

	delete bullet;
	bullet = nullptr;
}

void Game::Update()
{
	InvalidateRect(Hwnd, nullptr, TRUE);

	RECT temp;
	vector<DropRect>::iterator it = bullet->GetDropRects().begin();
	for (it; it != bullet->GetDropRects().end(); ++it)
	{
		if (PtInRect(&it->rect, cursorPosition))
		{
			score -= 5;
			bullet->GetDropRects().erase(it);
			break;
		}
		else if (IntersectRect(&temp, &player->GetRect(), &it->rect) == TRUE)
		{
			score -= 10;
			bullet->GetDropRects().erase(it);
			break;
		}
		else if (it->rect.top > WINDOWHEIGHT - 10)
		{
			score++;
		}
	}

	level = score / 20 + 1;
	if (level < 1)
		level = 1;

	bullet->SetLevel(level);

	player->Update();
	bullet->Update();
}

void Game::Render()
{
	PAINTSTRUCT ps;
	Hdc = BeginPaint(Hwnd, &ps);
	{	
		player->Render();
		bullet->Render();

		wstring str = L"점수 : " + to_wstring(score);
		TextOut(Hdc, 10, 10, str.c_str(), str.length());

		str = L"레벨 : " + to_wstring(level);
		TextOut(Hdc, 10, 30, str.c_str(), str.length());
	}
	EndPaint(Hwnd, &ps);
}
