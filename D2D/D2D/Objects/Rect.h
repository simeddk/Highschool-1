#pragma once

class Rect
{
public:
	Rect(Shader* shader);
	Rect(Shader* shader, Vector2 position, Vector2 scale, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	virtual ~Rect();

	virtual void Update();
	void Render();

private:
	void Initialize();
	void CreateBuffer();
	void ApplyTo();

public:
	void Position(float x, float y);
	void Position(Vector2& vec);
	Vector2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(Vector2& vec);
	Vector2 Scale() { return scale; }

	void Color(float r, float g, float b, float a = 1.0f);
	void Color(D3DXCOLOR& color);
	D3DXCOLOR Color() { return color; }

	void Pass(UINT val);

	Matrix World() { return world; }


private:
	struct Vertex
	{
		Vector3 Position;
		D3DXCOLOR Color;
	};

private:
	Shader* shader;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	Vector2 position;
	Vector2 scale;
	D3DXCOLOR color;

	Matrix world;

	ID3DX11EffectMatrixVariable* sWorld;
	ID3DX11EffectVectorVariable* sColor;

	PerFrame* perFrame = nullptr;

	UINT pass;
};