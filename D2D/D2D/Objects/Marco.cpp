#include "stdafx.h"
#include "Marco.h"

Marco::Marco(Shader* shader, Vector2 position, Vector2 scale)
	: shader(shader)
{
	animation = new Animation();

	perFrame = new PerFrame(shader);
	collider = new Collider();

	Clip* clip = nullptr;

	//Clips[0] - Idle
	{
		clip = new Clip(EPlayType::Loop);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 4, 2, 34, 40), 0.22f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 35, 2, 64, 40), 0.22f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 64, 2, 94, 40), 0.22f);
		animation->AddClip(clip);
	}

	//Clips[1] - Walk
	{
		clip = new Clip(EPlayType::Loop);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 0, 600, 32, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 33, 600, 64, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 65, 600, 96, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 97, 600, 124, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 125, 600, 154, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 158, 600, 188, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 191, 600, 222, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 224, 599, 258, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 259, 600, 294, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 295, 600, 326, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 329, 600, 360, 640), 0.1f);
		clip->AddFrame(new Sprite(shader, L"Marco.png", 362, 600, 393, 640), 0.1f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
}

Marco::~Marco()
{
	SafeDelete(animation);
	SafeDelete(perFrame);
	SafeDelete(collider);
}

void Marco::Update()
{
	Vector2 position = animation->Position();
	bool bMove = false;
	if (Key->Press('D'))
	{
		position.x += speed * Time::Delta();
		bMove = true;
		animation->RotationDegree(0, 0, 0);
	}
	else if (Key->Press('A'))
	{
		position.x -= speed * Time::Delta();
		bMove = true;
		animation->RotationDegree(0, 180, 0);
	}

	if (Key->Press('W'))
	{
		position.y += speed * Time::Delta();
		bMove = true;
	}
	else if (Key->Press('S'))
	{
		position.y -= speed * Time::Delta();
		bMove = true;
	}

	animation->Play(bMove ? 1 : 0);
	animation->Position(position);

	perFrame->Update();
	collider->Update(GetWorld());
	animation->Update();
}

void Marco::Render()
{
	perFrame->Render();
	animation->Render();
	collider->Render();
}

void Marco::Focus(Vector2* focusPosition)
{
	*focusPosition = animation->Position() + focusOffset;
}

Matrix Marco::GetWorld()
{
	return animation->GetCurrentFrameAsSprite()->World();
}

Sprite* Marco::GetSprite()
{
	return animation->GetCurrentFrameAsSprite();
}
