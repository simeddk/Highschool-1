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

	Collider* GetCollider() { return collider; }
	Matrix GetWorld();

	Sprite* GetSprite();

	void Position(Vector2& vec);
	Vector2 Position();

	void Scale(Vector2& vec);
	Vector2 Scale();

	void Rotation(Vector3& vec);
	Vector3 Rotation();

	void EnableGizmo() { bGizmo = true; }
	void DisableGizmo() { bGizmo = false; }

private:
	Shader* shader = nullptr;
	Animation* animation = nullptr;
	PerFrame* perFrame = nullptr;

	float speed = 200.0f;
	Vector2 focusOffset = Vector2(180, 140);

	Collider* collider = nullptr;

	class Gizmo* gizmo = nullptr;
	bool bGizmo = false;
};