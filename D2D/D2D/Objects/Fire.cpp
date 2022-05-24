#include "stdafx.h"
#include "Fire.h"

Fire::Fire(Shader* shader, Vector2 position, Vector2 scale)
	: position(position)
	, scale(scale)
{
	clip = new Clip(EPlayType::Loop);
	
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			float startX = (float)x * 43;
			float startY = (float)y * 67;
			float endX = ((float)x + 1) * 43;
			float endY = ((float)y + 1) * 67;

			clip->AddFrame(new Sprite(shader, L"FireSprite.png", startX, startY, endX, endY), 0.075f);
		}
	}

	clip->Play();

	clip->Position(this->position);
	clip->Scale(this->scale);

	collider = new Collider();
}

Fire::~Fire()
{
	SafeDelete(clip);
	SafeDelete(collider);
}

void Fire::Update()
{
	clip->Position(position);
	clip->Scale(scale);

	clip->Update();
	collider->Update(GetWorld());
}

void Fire::Render()
{
	clip->Render();
	collider->Render();
}

Matrix Fire::GetWorld()
{
	return clip->GetCurrentFrameAsSprite()->World();
}
