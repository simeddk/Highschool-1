#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
};