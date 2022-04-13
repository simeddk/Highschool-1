#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
	: delay(100)
	, level(1)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (delay >= 100)
	{
		DropRect dropRect;
		dropRect.rect.left = rand() % WINDOWWIDTH;
		dropRect.rect.right = dropRect.rect.left + 15;
		dropRect.rect.top = -15;
		dropRect.rect.bottom = 0;
		dropRect.dropSpeed = rand() % 5 + 2;

		dropRects.push_back(dropRect);

		delay = rand() % 100;
	}
	else
		delay += level;

	vector<DropRect>::iterator it;
	for (it = dropRects.begin(); it != dropRects.end(); ++it)
	{
		it->rect.top += it->dropSpeed;
		it->rect.bottom += it->dropSpeed;

		if (it->rect.top > WINDOWHEIGHT)
		{
			dropRects.erase(it);
			break;
		}
	}

}

void Bullet::Render()
{
	for (const auto& drop : dropRects)
		RECT_RENDER(drop.rect);
}
