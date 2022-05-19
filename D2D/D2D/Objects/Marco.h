#pragma once

#include "Viewer/IFollow.h"

class Marco : public IFollow
{
public:
	Marco(Shader* shader, Vector2 position, Vector2 scale);
	~Marco();

	void Update();
	void Render();

	void Focus(Vector2* focusPosition) override;

private:
	Shader* shader;
	Animation* animation = nullptr;

	float speed = 200.0f;
	Vector2 focusOffset = Vector2(180, 140);
};