#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
{
	D3DXMatrixIdentity(&world);

	shader = new Shader(L"05_Bounding.fx");
	sWorld = shader->AsMatrix("World");
	sColor = shader->AsVector("Color");

	perFrame = new PerFrame(shader);

	//Create VertexBuffer
	{
		Vertex vertices[5];
		vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = Vector3(+0.5f, +0.5f, 0.0f);
		vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[4].Position = Vector3(-0.5f, -0.5f, 0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}
}

Collider::~Collider()
{
	SafeDelete(shader);
	SafeDelete(perFrame);

	SafeRelease(vertexBuffer);
}

void Collider::Update(Matrix& world)
{
	this->world = world;
	perFrame->Update();
}

void Collider::Render()
{
	perFrame->Render();

	sWorld->SetMatrix(world);
	sColor->SetFloatVector(bHitted ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1));

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	shader->Draw(0, 0, 5);
}

bool Collider::Aabb(Matrix world, Vector2 position)
{
	Vector2 positionA = Vector2(world._41, world._42);
	Vector2 positionB = position;

	Vector2 distance;
	distance.x = fabsf(positionA.x - positionB.x);
	distance.y = fabsf(positionA.y - positionB.y);
	
	Vector2 halfSize;
	halfSize = Vector2(fabsf(world._11), fabsf(world._22)) * 0.5f;

	if (distance.x > halfSize.x) return false;
	if (distance.y > halfSize.y) return false;

	return true;
}

bool Collider::Aabb(Matrix world1, Matrix world2)
{
	Vector2 position1 = Vector2(world1._41, world1._42);
	Vector2 position2 = Vector2(world2._41, world2._42);;

	Vector2 distance;
	distance.x = fabsf(position1.x - position2.x);
	distance.y = fabsf(position1.y - position2.y);

	Vector2 halfSize1, halfSize2;
	halfSize1 = Vector2(fabsf(world1._11), fabsf(world1._22)) * 0.5f;
	halfSize2 = Vector2(fabsf(world2._11), fabsf(world2._22)) * 0.5f;

	if (distance.x > halfSize1.x + halfSize2.x) return false;
	if (distance.y > halfSize1.y + halfSize2.y) return false;

	return true;
}

bool Collider::Obb(Sprite* a, Sprite* b)
{
	ObbDesc A, B;
	Vector2 halfSize;

	halfSize = Vector2(a->TextureSize().x * a->Scale().x, a->TextureSize().y * a->Scale().y) * 0.5f;
	CreateObb(&A, halfSize, a->World());

	halfSize = Vector2(b->TextureSize().x * b->Scale().x, b->TextureSize().y * b->Scale().y) * 0.5f;
	CreateObb(&B, halfSize, b->World());

	Vector2 distance = a->Position() - b->Position();

	//a->Right축 검사
	float lengthA = D3DXVec2Length(&A.Length_Right);
	float lenghtB = fabsf(D3DXVec2Dot(&A.Right, &B.Length_Right)) + fabsf(D3DXVec2Dot(&A.Right, &B.Length_Up));
	float length = fabsf(D3DXVec2Dot(&A.Right, &distance));
	if (length > lengthA + lenghtB) return false;

	//a->Up축 검사
	lengthA = D3DXVec2Length(&A.Length_Up);
	lenghtB = fabsf(D3DXVec2Dot(&A.Up, &B.Length_Up)) + fabsf(D3DXVec2Dot(&A.Up, &B.Length_Up));
	length = fabsf(D3DXVec2Dot(&A.Up, &distance));
	if (length > lengthA + lenghtB) return false;

	//b->Right축 검사
	lengthA = D3DXVec2Length(&B.Length_Right);
	lenghtB = fabsf(D3DXVec2Dot(&B.Right, &A.Length_Right)) + fabsf(D3DXVec2Dot(&B.Right, &A.Length_Up));
	length = fabsf(D3DXVec2Dot(&B.Right, &distance));
	if (length > lengthA + lenghtB) return false;

	//b->Up축 검사
	lengthA = D3DXVec2Length(&B.Length_Up);
	lenghtB = fabsf(D3DXVec2Dot(&B.Up, &A.Length_Right)) + fabsf(D3DXVec2Dot(&B.Up, &A.Length_Up));
	length = fabsf(D3DXVec2Dot(&B.Up, &distance));
	if (length > lengthA + lenghtB) return false;

	return true;
}

void Collider::CreateObb(ObbDesc* out, Vector2& half, Matrix& transform)
{
	D3DXVec2Normalize(&out->Right, &Vector2(transform._11, transform._12));
	D3DXVec2Normalize(&out->Up, &Vector2(transform._21, transform._22));

	out->HalfSize = half;
	out->Length_Right = out->Right * out->HalfSize.x;
	out->Length_Up = out->Up * out->HalfSize.y;
}
