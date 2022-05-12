#pragma once

class Marco
{
public:
	Marco(Shader* shader, Vector2 position, Vector2 scale);
	~Marco();

	void Update();
	void Render();

private:
	Shader* shader;
	Animation* animation = nullptr;

	float speed = 200.0f;
};