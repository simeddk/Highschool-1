#pragma once

class Freedom : public Camera
{
public:
	Freedom(float speed = 2000.0f);
	~Freedom();

	void Update() override;

	void Speed(float val);

private:
	void Move(Vector2 translation);

private:
	float speed;

};