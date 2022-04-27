#pragma once
#include "Rect.h"

class MovableRect : public Rect
{
public:
	MovableRect(Shader* shader);
	MovableRect(Shader* shader, Vector2 position, Vector2 scale, D3DXCOLOR color);

	void MoveLeft();
	void MoveRight();

	void MoveSpeed(float val);
	float MoveSpeed() { return moveSpeed; }

private:
	float moveSpeed = 0.1f;
};
