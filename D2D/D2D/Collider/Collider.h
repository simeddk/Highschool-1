#pragma once

class Collider
{
public:
	Collider();
	~Collider();

	void Update(Matrix& world);
	void Render();

	void SetHit() { bHitted = true; }
	void SetMiss() { bHitted = false; }
	bool IsHitted() { return bHitted; }

public:
	static bool Aabb(Matrix world, Vector2 position);
	static bool Aabb(Matrix world1, Matrix world2);

private:
	struct Vertex
	{
		Vector3 Position;
	};

private:
	Shader* shader = nullptr;
	ID3D11Buffer* vertexBuffer = nullptr;

	Matrix world;
	ID3DX11EffectMatrixVariable* sWorld;

	bool bHitted = false;
	ID3DX11EffectVectorVariable* sColor;

	PerFrame* perFrame = nullptr;
};