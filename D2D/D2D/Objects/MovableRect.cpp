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

void MovableRect::Update(Matrix& V, Matrix& P)
{
	__super::Update(V, P);
	
	Vector2 position = Position();

	if (bGround == false)
	{
		velocity -= gravity * Time::Delta();
		position.y += velocity;
	}

	if (position.y < Scale().y * 0.5f)
	{
		bGround = true;
		velocity = 0.0f;
		position.y = Scale().y * 0.5f;
	}

	Position(position);

	ImGui::TextColored(velocity > 0.0f ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1), "%.2f", velocity);
	ImGui::LabelText("Height", "%.2f", position.y);
	ImGui::LabelText("IsGround", "%d", bGround);

}

void MovableRect::MoveLeft()
{
	Vector2 position = Position();
	position.x -= moveSpeed * Time::Delta();
	Position(position);
}

void MovableRect::MoveRight()
{
	Vector2 position = Position();
	position.x += moveSpeed * Time::Delta();
	Position(position);
}

void MovableRect::Jump()
{
	if (bGround == true)
	{
		velocity = 0.4f;
		bGround = false;
	}
}

void MovableRect::StopJump()
{
	if (velocity > 0)
		velocity = 0;
}

void MovableRect::MoveSpeed(float val)
{
	moveSpeed = val;
}
