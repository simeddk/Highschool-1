#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse()
{
	ZeroMemory(buttonStatus, sizeof(BYTE) * MAX_MOUSE_INPUT);
	ZeroMemory(buttonPrevStatus, sizeof(BYTE) * MAX_MOUSE_INPUT);
	ZeroMemory(buttonMap, sizeof(EButtonState) * MAX_MOUSE_INPUT);
	ZeroMemory(buttonCount, sizeof(int) * MAX_MOUSE_INPUT);

	doubleClickTime = GetDoubleClickTime();
	startDoubleClickTime[0] = GetTickCount();

	for (int i = 1; i < MAX_MOUSE_INPUT; i++)
		startDoubleClickTime[i] = startDoubleClickTime[0];
}

CMouse::~CMouse()
{
}

void CMouse::Update()
{
	//���� �����ӿ��� ����ߴ� buttonStatus�� buttonPrevStatus�� ����
	memcpy(buttonPrevStatus, buttonStatus, sizeof(BYTE) * MAX_MOUSE_INPUT);

	//���� ���� �˻��ϱ� ���� �α׸� ������
	ZeroMemory(buttonStatus, sizeof(BYTE) * MAX_MOUSE_INPUT);
	ZeroMemory(buttonMap, sizeof(EButtonState) * MAX_MOUSE_INPUT);

	//���� ���� ����
	buttonStatus[(int)LButton] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[(int)RButton] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[(int)MButton] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (UINT i = 0; i < MAX_MOUSE_INPUT; i++)
	{
		//���� ���� vs ���� ���� �� -> ������.. �ٿ�����.. ��� ����� ButtonMap�� ����
		BYTE prevStatus = buttonPrevStatus[i];
		BYTE currentStatus = buttonStatus[i];

		if (prevStatus == 0 && currentStatus == 1)
			buttonMap[i] = EButtonState::Down;
		else if (prevStatus == 1 && currentStatus == 0)
			buttonMap[i] = EButtonState::Up;
		else if (prevStatus == 1 && currentStatus == 1)
			buttonMap[i] = EButtonState::Press;
	}//for

	//���� ȭ�� �ٱ����� ���Ե� Ŀ�� ��ġ ���ϱ�
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(Hwnd, &point);
	wheelOldStatus.x = wheelStatus.x;
	wheelOldStatus.y = wheelStatus.y;
	wheelStatus.x = (float)point.x;
	wheelStatus.y = (float)point.y;

	//��Ÿ Ŀ�� ��ġ ���ϱ�
	wheelMoveValue = wheelStatus - wheelOldStatus;

	//��Ÿ �� ���ϱ�
	wheelOldStatus.z = wheelStatus.z;

	//����Ŭ��
	DWORD time = GetTickCount();
	for (UINT i = 0; i < MAX_MOUSE_INPUT; i++)
	{
		if (buttonMap[i] == EButtonState::Down)
		{
			if (buttonCount[i] == 1)
			{
				if (time - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}

			buttonCount[i]++;

			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = time;
		}//if(Down)

		if (buttonMap[i] == EButtonState::Up)
		{
			if (buttonCount[i] == 2)
			{
				if (time - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
				else if (time - startDoubleClickTime[i] < doubleClickTime)
				{
					buttonMap[i] = EButtonState::DoubleClick;
					buttonCount[i] = 0;
				}
			}
		}//if(Up)

	}//for
}

void CMouse::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	if (message == WM_MOUSEWHEEL)
	{
		short tWheelValue = HIWORD(wParam);

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z += (float)tWheelValue;
	}
}

Vector2 CMouse::Position_World()
{
	Vector2 mousePosition;
	mousePosition.x = ((position.x / Width) * 2.0f) - 1.0f;
	mousePosition.y = (((position.y / Height) * 2.0f) - 1.0f) * -1.0f;

	Matrix vp = Context::Get()->GetCamera()->View() * Context::Get()->GetProjection();
	D3DXMatrixInverse(&vp, nullptr, &vp);

	D3DXVec2TransformCoord(&mousePosition, &mousePosition, &vp);

	return mousePosition;

}
