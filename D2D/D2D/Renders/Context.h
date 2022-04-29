#pragma once

class Context
{
public:
	static void Create();
	static void Delete();
	static Context* Get();

private:
	Context();
	~Context();

public:
	void SetShader(Shader* shader);
	void Update();
	void Render();

	const Matrix& GetView() { return desc.View; }
	const Matrix& GetProjection() { return desc.Projection; }

private:
	struct ViewProjectionDesc
	{
		Matrix View;
		Matrix Projection;
	} desc;

private:
	static Context* instance;

private:
	Shader* shader = nullptr;
	ID3D11Buffer* viewProjectionBuffer = nullptr;
	ID3DX11EffectConstantBuffer* sViewProjectionBuffer = nullptr;

};