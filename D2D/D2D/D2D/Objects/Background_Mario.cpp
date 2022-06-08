#include "stdafx.h"
#include "Background_Mario.h"

Background_Mario::Background_Mario(Shader* shader)
{
	cloud[0] = new Sprite(shader, L"Cloud.png", 137, 128);
	cloud[1] = new Sprite(shader, L"Cloud.png", 140, 0, 344, 128);
	
	tile = new Sprite(shader, L"Tile.png");

	bush[0] = new Sprite(shader, L"Bush.png");
	bush[1] = new Sprite(shader, L"Bush2.png");
}

Background_Mario::~Background_Mario()
{
	SafeDelete(cloud[0]);
	SafeDelete(cloud[1]);
	SafeDelete(tile);
	SafeDelete(bush[0]);
	SafeDelete(bush[1]);
}

void Background_Mario::Update()
{
	cloud[0]->Update();
	cloud[1]->Update();

	tile->Update();

	bush[0]->Update();
	bush[1]->Update();
}

void Background_Mario::Render()
{
	cloud[0]->Position(240, 600);
	cloud[0]->Render();

	cloud[0]->Position(500, 600);
	cloud[0]->Render();

	cloud[1]->Position(900, 500);
	cloud[1]->Render();

	bush[1]->Position(150, 190);
	bush[1]->Render();

	bush[1]->Position(500, 190);
	bush[1]->Render();

	bush[1]->Position(800, 190);
	bush[1]->Render();

	bush[0]->Position(300, 140);
	bush[0]->Render(); 

	bush[0]->Position(950, 140);
	bush[0]->Render();

	float tileWidth = tile->TextureSize().x * tile->Scale().x;

	for (int i = 0; i < 9; i++)
	{
		tile->Position(i * tileWidth, 64);
		tile->Render();
	}
}
