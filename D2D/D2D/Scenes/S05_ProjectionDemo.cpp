#include "stdafx.h"
#include "S05_ProjectionDemo.h"


S05_ProjectionDemo::S05_ProjectionDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	background = new Sprite(shader, L"Background/SonicStage.png");
	perFrame = new PerFrame(shader);

	Freedom* freedom = dynamic_cast<Freedom*>(Context::Get()->GetCamera());
	if (freedom != nullptr)
		freedom->Speed(500);
}

S05_ProjectionDemo::~S05_ProjectionDemo()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(perFrame);
}

void S05_ProjectionDemo::Update()
{
	perFrame->Update();
	background->Update();
}

void S05_ProjectionDemo::Render()
{
	perFrame->Render();
	background->Render();
}