#pragma once

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update();

	void Position(float x, float y);
	void Position(Vector2& vec);
	Vector2 Position() { return position; }

	float& Depth() { return depth; }

	Matrix View() { return view; }

protected:
	Vector2 position = Vector2(0, 0);
	float depth = 0.0f;

private:
	Matrix view;
};