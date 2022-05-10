#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Shader* shader, Vector2 start, float angle, float speed)
	: position(start)
{
	sprite = new Sprite(shader, L"bullet.png", 37, 116, 53, 133);
	sprite->Position(position);
	sprite->Scale(sprite->TextureSize());

	float radian = Math::ToRadian(angle);
	Vector2 direction;
	direction.x = cosf(radian);
	direction.y = sinf(radian);

	velocity = direction * speed;
}

Bullet::~Bullet()
{
	SafeDelete(sprite);
}

void Bullet::Update()
{
	position += velocity * Time::Delta();
	sprite->Position(position);
}

void Bullet::Render()
{
	sprite->Render();
}
