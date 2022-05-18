#include "stdafx.h"
#include "Sprite.h"

//--------------------------------------------------------------------------
// Sprite
//--------------------------------------------------------------------------
Sprite::Sprite(Shader* shader, wstring textureFile)
{
	Initialize(shader, textureFile, 0, 0, 0, 0);
}

Sprite::Sprite(Shader* shader, wstring textureFile, float cropEndX, float cropEndY)
{
	Initialize(shader, textureFile, 0, 0, cropEndX, cropEndY);
}

Sprite::Sprite(Shader* shader, wstring textureFile, float cropStartX, float cropStartY, float cropEndX, float cropEndY)
{
	Initialize(shader, textureFile, cropStartX, cropStartY, cropEndX, cropEndY);
}

void Sprite::Initialize(Shader* shader, wstring textureFile, float cropStartX, float cropStartY, float cropEndX, float cropEndY)
{
	this->shader = shader;
	this->textureFile = L"../../_Textures/" + textureFile;

	srv = SpriteSRV::GetSRV(this->textureFile);
	sSrv = this->shader->AsSRV("DiffuseMap");

	D3DX11_IMAGE_INFO info;
	Check(D3DX11GetImageInfoFromFile(this->textureFile.c_str(), nullptr, &info, nullptr));

	cropStartX = (cropStartX > 0) ? cropStartX / (float)info.Width : 0.0f;
	cropStartY = (cropStartY > 0) ? cropStartY / (float)info.Height : 0.0f;
	cropEndX = (cropEndX > 0) ? cropEndX / (float)info.Width : 1.0f;
	cropEndY = (cropEndY > 0) ? cropEndY / (float)info.Height : 1.0f;

	//Vertex Data
	Vertex vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(cropStartX,	cropEndY);
	vertices[1].Uv = Vector2(cropStartX,	cropStartY);
	vertices[2].Uv = Vector2(cropEndX,		cropEndY);
	vertices[3].Uv = Vector2(cropEndX,		cropStartY);
	
	//TextureSize
	float sizeX = (cropEndX > 0) ? cropEndX * (float)info.Width : (float)info.Width;
	sizeX -= cropStartX * (float)info.Width;

	float sizeY = (cropEndY > 0) ? cropEndY * (float)info.Height : (float)info.Height;
	sizeY -= cropStartY * (float)info.Height;

	textureSize = Vector2(sizeX, sizeY);

	//GetParams & DefaultWorld
	sWorld = this->shader->AsMatrix("World");
	UpdateWorld();
	
	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create IndexBuffer
	UINT indices[] = { 0, 1, 2, 2, 1, 3 };
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(Device->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}

Sprite::~Sprite()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);

	SpriteSRV::RemoveSRV(textureFile);
}


void Sprite::Update()
{
}

void Sprite::Render()
{
	//Transform
	sWorld->SetMatrix(world);

	//DiffuseMap
	sSrv->SetResource(srv);

	//DrawCall
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, pass, 6);
}

Vector2 Sprite::ScaledTextureSize()
{
	return Vector2(textureSize.x * scale.x, textureSize.y * scale.y);
}

void Sprite::Position(float x, float y)
{
	Position(Vector2(x, y));
}

void Sprite::Position(Vector2& vec)
{
	position = vec;

	UpdateWorld();
}

void Sprite::Scale(float x, float y)
{
	Scale(Vector2(x, y));
}

void Sprite::Scale(Vector2& vec)
{
	scale = vec;

	UpdateWorld();
}

void Sprite::Rotation(float x, float y, float z)
{
	Rotation(Vector3(x, y, z));
}

void Sprite::Rotation(Vector3& vec)
{
	rotation = vec;

	UpdateWorld();
}

void Sprite::RotationDegree(float x, float y, float z)
{
	RotationDegree(Vector3(x, y, z));
}

void Sprite::RotationDegree(Vector3& vec)
{
	vec.x =	Math::ToRadian(vec.x);
	vec.y =	Math::ToRadian(vec.y);
	vec.z =	Math::ToRadian(vec.z);

	Rotation(vec);
}

Vector3 Sprite::RotationDegree()
{
	Vector3 vec;
	vec.x = Math::ToDegree(rotation.x);
	vec.y = Math::ToDegree(rotation.y);
	vec.z = Math::ToDegree(rotation.z);

	return vec;
}

Vector3 Sprite::Right()
{
	Vector3 vec;
	D3DXVec3Normalize(&vec, &Vector3(world._11, world._12, world._13));
	
	return vec;
}

Vector3 Sprite::Up()
{
	Vector3 vec;
	D3DXVec3Normalize(&vec, &Vector3(world._21, world._22, world._23));

	return vec;
}

Vector3 Sprite::Foward()
{
	Vector3 vec;
	D3DXVec3Normalize(&vec, &Vector3(world._31, world._32, world._33));

	return vec;
}

void Sprite::UpdateWorld()
{
	Matrix S, R, T;
	D3DXMatrixScaling(&S, textureSize.x * scale.x, textureSize.y * scale.y, 1);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, 0);
	world = S * R * T;

	//sWorld->SetMatrix(world);
}

//--------------------------------------------------------------------------
// SpriteSRV
//--------------------------------------------------------------------------
map<wstring, SpriteSRV::SpriteDesc> SpriteSRV::spriteMap;

ID3D11ShaderResourceView* SpriteSRV::GetSRV(wstring textureFile)
{
	if (spriteMap.count(textureFile) > 0)
	{
		spriteMap[textureFile].ReferenceCount++;

		return spriteMap[textureFile].SRV;
	}

	ID3D11ShaderResourceView* srv;
	Check(D3DX11CreateShaderResourceViewFromFile(Device, textureFile.c_str(), nullptr, nullptr, &srv, nullptr));

	SpriteDesc desc;
	desc.ReferenceCount++;
	desc.SRV = srv;

	spriteMap[textureFile] = desc;

	return desc.SRV;
}

void SpriteSRV::RemoveSRV(wstring textureFile)
{
	UINT count = spriteMap.count(textureFile);
	assert(count > 0);

	spriteMap[textureFile].ReferenceCount--;

	if (spriteMap[textureFile].ReferenceCount < 1) 
	{
		SafeRelease(spriteMap[textureFile].SRV);
		spriteMap.erase(textureFile);
	}
}
