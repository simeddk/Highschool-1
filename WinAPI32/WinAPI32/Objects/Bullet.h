#pragma once

#include "GameObject.h"

struct DropRect
{
	RECT rect;
	LONG dropSpeed;
};

class Bullet final : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Update() override;
	void Render() override;

	vector<DropRect>& GetDropRects() { return dropRects; }
	void SetLevel(int level) { this->level = level; }

private:
	int delay;
	int level;

	vector<DropRect> dropRects;
};