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
	static bool Obb(Sprite* a, Sprite* b);

private:
	struct Vertex
	{
		Vector3 Position;
	};

	struct ObbDesc
	{
		Vector2 HalfSize; //그림의 절반 사이즈

		Vector2 Right; //방향 벡터
		Vector2 Up; //방향 벡터

		Vector2 Length_Right; //방향 벡터 * 그림의 절반 사이즈 -> 엣지
		Vector2 Length_Up;//방향 벡터 * 그림의 절반 사이즈 -> 엣지
	};

private:
	static void CreateObb(ObbDesc* out, Vector2& half, Matrix& transform);

private:
	Shader* shader = nullptr;
	ID3D11Buffer* vertexBuffer = nullptr;

	Matrix world;
	ID3DX11EffectMatrixVariable* sWorld;

	bool bHitted = false;
	ID3DX11EffectVectorVariable* sColor;

	PerFrame* perFrame = nullptr;
};