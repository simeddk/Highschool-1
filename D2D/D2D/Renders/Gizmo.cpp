#include "stdafx.h"
#include "Gizmo.h"

void Gizmo::Set(Sprite* sprite, Vector2* outScale, Vector3* outRotation, Vector2* outPosition, int id)
{
	ImGuizmo::SetOrthographic(true);
	ImGuizmo::BeginFrame();
	ImGuizmo::SetID(id);

	if (Key->Press(VK_LCONTROL))
	{
		if (Key->Down('W'))
			operation = ImGuizmo::OPERATION::TRANSLATE;
		else if (Key->Down('E'))
			operation = ImGuizmo::OPERATION::ROTATE;
		else if (Key->Down('R'))
			operation = ImGuizmo::OPERATION::SCALE;
		else if (Key->Down('Q'))
			mode = (ImGuizmo::MODE)!mode;
	}

	ImGuizmo::SetRect(0, 0, Width, Height);

	Matrix V = Context::Get()->GetView();
	Matrix P = Context::Get()->GetProjection();
	ImGuizmo::Manipulate(V, P, operation, mode, sprite->World());

	Vector3 s, r, t;
	Math::MatrixDecompose(sprite->World(), s, r, t);

	*outRotation = r;
	*outPosition = Vector2(t.x, t.y);
	*outScale = Vector2(s.x / sprite->TextureSize().x, s.y / sprite->TextureSize().y);

	int a = 0;
}
