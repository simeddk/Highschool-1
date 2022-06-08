#include "stdafx.h"
#include "Freedom.h"

Freedom::Freedom(float speed)
	: speed(speed)
{
}

Freedom::~Freedom()
{
}

void Freedom::Update()
{
	if (Mouse->Press(RButton))
	{
		Vector2 mouseDelta = Vector2(Mouse->Position_Delta().x * -1.0f, Mouse->Position_Delta().y);
		Move(mouseDelta * speed);

	}
	__super::Update();
}

void Freedom::Speed(float val)
{
	speed = val;
}

void Freedom::Move(Vector2 translation)
{
	position += translation * Time::Delta();
}
