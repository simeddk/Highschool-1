#pragma once

#define MAX_MOUSE_INPUT 8

enum class EButtonState { None, Down, Up, Press, DoubleClick };
enum EMouseButton { LButton, RButton, MButton };

class CMouse
{
public:
	CMouse();
	~CMouse();

	void Update();

	void WndProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	//���� ȭ�� �󿡼��� Ŀ�� ��ġ ����
	Vector2 Position_OnViewport() { return position; }

	//���� ȭ�� �ٱ�����, ��ü ȭ�� �ػ� �������� Ŀ�� ��ġ ����
	Vector2 Position_OnClient() { return Vector2(wheelStatus.x, wheelStatus.y); }

	//���� �����Ӱ� ���� �������� Ŀ�� ��ġ ����x
	Vector2 Position_Delta() { return Vector2(wheelMoveValue.x, wheelMoveValue.y); }
	float Wheel_Delta() { return wheelMoveValue.z; }

	//�Է� �̺�Ʈ
public:
	bool Down(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Down; }
	bool Up(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Up; }
	bool Press(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Press; }
	bool DoubleClick(EMouseButton button) { return buttonMap[(int)button] == EButtonState::DoubleClick; }

private:
	Vector2 position = Vector2(0, 0); //���콺 Ŀ���� ��ġ

	BYTE buttonStatus[MAX_MOUSE_INPUT]; //���� ��ư�� ���� ����
	BYTE buttonPrevStatus[MAX_MOUSE_INPUT]; //������ ��ư�� ���� ����
	EButtonState buttonMap[MAX_MOUSE_INPUT]; //��ư�� Down, Up, DoubleClick �� � �������� ����

	DWORD doubleClickTime; //����Ŭ�� ��� �ð�
	DWORD startDoubleClickTime[MAX_MOUSE_INPUT]; //����Ŭ�� ���� �ð�
	int buttonCount[MAX_MOUSE_INPUT]; //��ư Ŭ�� Ƚ��

private:
	Vector3 wheelStatus = Vector3(0, 0, 0); //xy : ���콺 Ŀ���� ��ġ, z : �ٰ�
	Vector3 wheelOldStatus = Vector3(0, 0, 0); //�Ʒ� ����(��Ÿ��)�� ���ϱ� ���� ����
	Vector3 wheelMoveValue = Vector3(0, 0, 0); //���� �����Ӱ� ���� �������� ��Ÿ ����
};