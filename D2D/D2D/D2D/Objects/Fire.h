#pragma once

class Fire
{
public:
	Fire(Shader* shader, Vector2 position, Vector2 scale);
	~Fire();

	void Update();
	void Render();

	Vector2& Position() { return position; }
	Vector2& Scale() { return scale; }

	Matrix GetWorld();
	Collider* GetCollider() { return collider; }

	void Play();
	void Stop();

	void EnableGizmo() { bGizmo = true; }
	void DisableGizmo() { bGizmo = false; }

	Sprite* GetSprite();

private:
	Clip* clip;
	class Gizmo* gizmo = nullptr;

	Vector2 position;
	Vector2 scale;

	Collider* collider = nullptr;
	bool bGizmo = false;
};