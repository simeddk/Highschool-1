#include "stdafx.h"
#include "S02_Scene02Demo.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

S02_Scene02Demo::S02_Scene02Demo()
{
	shader = new Shader(L"04_Sprite.fx");
	perFrame = new PerFrame(shader);

	background = new Sprite(shader, L"Background/FinalFightStage.png");
	background->Scale(2.5f, 2.5f);
	background->Position(400, 300);

	Context::Get()->SetFreedomMode();
}

S02_Scene02Demo::~S02_Scene02Demo()
{
	SafeDelete(shader);
	SafeDelete(perFrame);
	SafeDelete(background);
}

void S02_Scene02Demo::Update()
{
	Follow* follow = dynamic_cast<Follow*>(Context::Get()->GetCamera());
	if (follow != nullptr)
		Context::Get()->SetFreedomMode();

	perFrame->Update();
	background->Update();
}

void S02_Scene02Demo::Render()
{
	perFrame->Render();
	background->Render();
}