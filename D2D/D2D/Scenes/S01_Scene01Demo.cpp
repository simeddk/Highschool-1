#include "stdafx.h"
#include "S01_Scene01Demo.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

S01_Scene01Demo::S01_Scene01Demo()
{
	shader = new Shader(L"04_Sprite.fx");
	perFrame = new PerFrame(shader);

	background = new Background_Mario(shader);

	marco = new Marco(shader, Vector2(100, 170), Vector2(2.5f, 2.5f));
	Context::Get()->SetFollowMode(marco);
}

S01_Scene01Demo::~S01_Scene01Demo()
{
	SafeDelete(shader);
	SafeDelete(perFrame);
	SafeDelete(background);
	SafeDelete(marco);
}

void S01_Scene01Demo::Update()
{
	perFrame->Update();
	background->Update();
	marco->Update();
}

void S01_Scene01Demo::Render()
{
	perFrame->Render();
	background->Render();
	marco->Render();
}