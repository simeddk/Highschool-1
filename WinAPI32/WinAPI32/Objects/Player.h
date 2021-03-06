#pragma once

#include "GameObject.h"

class Player final : public GameObject
{
public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

	RECT& GetRect() { return rect; }

private:
	RECT rect;
	POINT position;
	LONG moveSpeed;

};