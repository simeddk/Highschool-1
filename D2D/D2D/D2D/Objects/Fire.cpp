#include "stdafx.h"
#include "Fire.h"
#include "Renders/Gizmo.h"

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
	gizmo = new Gizmo();


}

Fire::~Fire()
{
	SafeDelete(clip);
	SafeDelete(collider);
	SafeDelete(gizmo);
}

void Fire::Update()
{
	clip->Update();
	collider->Update(GetWorld());

	CheckFalse(bGizmo);
	Vector2 scale, translate;
	Vector3 rotation;
	gizmo->Set(clip->GetCurrentFrameAsSprite(), &scale, &rotation, &translate);
	clip->Position(translate);
	clip->Scale(scale);
	clip->Rotation(rotation);
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

void Fire::Play()
{
	clip->Play();
}

void Fire::Stop()
{
	clip->Stop();
}

Sprite* Fire::GetSprite()
{
	return clip->GetCurrentFrameAsSprite();
}
