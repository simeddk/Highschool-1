#pragma once

class PerFrame
{
public:
	PerFrame(Shader* shader);
	~PerFrame();

	void Update();
	void Render();

private:
	struct ViewProjectionDesc
	{
		Matrix View;
		Matrix Projection;
	} desc;

private:
	Shader* shader = nullptr;
	ID3D11Buffer* viewProjectionBuffer = nullptr;
	ID3DX11EffectConstantBuffer* sViewProjectionBuffer = nullptr;
};