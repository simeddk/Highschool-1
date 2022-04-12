#include "stdafx.h"
#include "Player.h"

Player::Player()
	: moveSpeed(20)
{
	position = { WINDOWWIDTH / 2, WINDOWHEIGHT - 65 };
	ZeroMemory(&rect, sizeof(RECT));
}

Player::~Player()
{
}

void Player::Update()
{
	if (GetAsyncKeyState('A') & 0x8000)
		position.x -= (position.x - 12 >= 0) ? moveSpeed : 0;
	else if (GetAsyncKeyState('D') & 0x8000)
		position.x += (position.x <= WINDOWWIDTH - 25) ? moveSpeed : 0;

	rect = RECT_INIT(position.x, position.y, 50);
}

void Player::Render()
{
	RECT_RENDER(rect);
}
