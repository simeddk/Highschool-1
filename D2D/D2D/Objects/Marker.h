#pragma once

class Marker
{
public:
	Marker(Shader* shader, Vector2 position);
	~Marker();

	void Update();
	void Render();

	Vector2 Position() { return position; }

private:
	Clip* clip;

	Vector2 position;
};