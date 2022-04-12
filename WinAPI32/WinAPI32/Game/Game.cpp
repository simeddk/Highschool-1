#include "stdafx.h"
#include "Game.h"
#include "Objects/Player.h"

Game::Game()
{
	player = new Player();
}

Game::~Game()
{
	delete player;
	player = nullptr;
}

void Game::Update()
{
	player->Update();
}

void Game::Render()
{
	player->Render();
}
//19:01