#pragma once
#include "Rect.h"

class MovableRect : public Rect
{
public:
	MovableRect(Shader* shader);
	MovableRect(Shader* shader, Vector2 position, Vector2 scale, D3DXCOLOR color);

	void Update() override;

	void MoveLeft();
	void MoveRight();

	void Jump();
	void StopJump();

	void MoveSpeed(float val);
	float MoveSpeed() { return moveSpeed; }

private:
	float moveSpeed = 400.0f;

	float velocity = 0.0f;
	float gravity = 1.2f;
	bool bGround = true;
};
