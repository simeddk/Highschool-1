#include "stdafx.h"
#include "Game.h"
#include "Objects/Player.h"

Game::Game()
{
	srand((UINT)time(nullptr));
	player = new Player();
}

Game::~Game()
{
	delete player;
	player = nullptr;
}

void Game::Update()
{
	InvalidateRect(Hwnd, nullptr, TRUE);

	player->Update();
}

void Game::Render()
{
	PAINTSTRUCT ps;
	Hdc = BeginPaint(Hwnd, &ps);
	{
		player->Render();
	}
	EndPaint(Hwnd, &ps);
}
