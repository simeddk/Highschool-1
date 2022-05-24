#pragma once

class Fire
{
public:
	Fire(Shader* shader, Vector2 position, Vector2 scale);
	~Fire();

	void Update();
	void Render();

	void Position(Vector2& vec) { position = vec; }
	Vector2 Position() { return position; }

	void Scale(Vector2& vec) { scale = vec; }
	Vector2 Scale() { return scale; }

	Matrix GetWorld();
	Collider* GetCollider() { return collider; }

private:
	Clip* clip;

	Vector2 position;
	Vector2 scale;

	Collider* collider = nullptr;
};