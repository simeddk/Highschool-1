#include "stdafx.h"
#include "MovableRect.h"

MovableRect::MovableRect(Shader* shader)
	: Rect(shader)
{
}

MovableRect::MovableRect(Shader* shader, Vector2 position, Vector2 scale, D3DXCOLOR color)
	: Rect(shader, position, scale, color)
{
}

void MovableRect::MoveLeft()
{
	Vector2 position = Position();
	position.x -= moveSpeed;
	Position(position);
}

void MovableRect::MoveRight()
{
	Vector2 position = Position();
	position.x += moveSpeed;
	Position(position);
}

void MovableRect::MoveSpeed(float val)
{
	moveSpeed = val;
}
