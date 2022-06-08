#pragma once

//--------------------------------------------------------------------------
// Sprite
//--------------------------------------------------------------------------
class Sprite
{
public:
	Sprite(Shader* shader, wstring textureFile);
	Sprite(Shader* shader, wstring textureFile, float cropEndX, float cropEndY);
	Sprite(Shader* shader, wstring textureFile, float cropStartX, float cropStartY, float cropEndX, float cropEndY);
	~Sprite();

private:
	void Initialize(Shader* shader, wstring textureFile, float cropStartX, float cropStartY, float cropEndX, float cropEndY);
	void UpdateWorld();

public:
	void Update();
	void Render();

	void Pass(UINT pass) { this->pass = pass; }
	Shader* GetShader() { return shader; }
	Matrix& World() { return world; }
	
	Vector2 TextureSize() { return textureSize; }
	Vector2 ScaledTextureSize();

	Vector2 StartUV() { return startUV; }
	Vector2 EndUV() { return endUV; }
	ID3D11ShaderResourceView* SRV() { return srv; }

	wstring GetTextureFile() { return textureFile; }

public:
	void Position(float x, float y);
	void Position(Vector2& vec);
	Vector2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(Vector2& vec);
	Vector2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(Vector3& vec);
	Vector3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(Vector3& vec);
	Vector3 RotationDegree();

	Vector3 Right();
	Vector3 Up();
	Vector3 Foward();


private:
	struct Vertex
	{
		Vector3 Position;
		Vector2 Uv;
	};

private:
	Shader* shader;
	UINT pass = 0;

	wstring textureFile;
	ID3D11ShaderResourceView* srv = nullptr;
	ID3DX11EffectShaderResourceVariable* sSrv;
	Vector2 textureSize;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	Vector2 position = Vector2(0, 0);
	Vector2 scale = Vector2(1, 1);
	Vector3 rotation = Vector3(0, 0, 0);

	Matrix world;
	ID3DX11EffectMatrixVariable* sWorld;

	Vector2 startUV;
	Vector2 endUV;
};

//--------------------------------------------------------------------------
// SpriteSRV
//--------------------------------------------------------------------------
class SpriteSRV
{
private:
	friend class Sprite;

private:
	static ID3D11ShaderResourceView* GetSRV(wstring textureFile);
	static void RemoveSRV(wstring textureFile);

private:
	struct SpriteDesc
	{
		UINT ReferenceCount = 0;
		ID3D11ShaderResourceView* SRV = nullptr;
	};

private:
	static map<wstring, SpriteDesc> spriteMap;
};