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
	//게임 화면 상에서만 커서 위치 리턴
	Vector2 Position_OnViewport() { return position; }

	//게임 화면 바깥까지, 전체 화면 해상도 관점에서 커서 위치 리턴
	Vector2 Position_OnClient() { return Vector2(wheelStatus.x, wheelStatus.y); }

	//이전 프레임과 현재 프레임의 커서 위치 차이x
	Vector2 Position_Delta() { return Vector2(wheelMoveValue.x, wheelMoveValue.y); }
	float Wheel_Delta() { return wheelMoveValue.z; }

	//입력 이벤트
public:
	bool Down(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Down; }
	bool Up(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Up; }
	bool Press(EMouseButton button) { return buttonMap[(int)button] == EButtonState::Press; }
	bool DoubleClick(EMouseButton button) { return buttonMap[(int)button] == EButtonState::DoubleClick; }

private:
	Vector2 position = Vector2(0, 0); //마우스 커서의 위치

	BYTE buttonStatus[MAX_MOUSE_INPUT]; //현재 버튼이 눌린 상태
	BYTE buttonPrevStatus[MAX_MOUSE_INPUT]; //이전에 버튼이 눌린 상태
	EButtonState buttonMap[MAX_MOUSE_INPUT]; //버튼이 Down, Up, DoubleClick 중 어떤 상태인지 저장

	DWORD doubleClickTime; //더블클릭 허용 시간
	DWORD startDoubleClickTime[MAX_MOUSE_INPUT]; //더블클릭 시작 시간
	int buttonCount[MAX_MOUSE_INPUT]; //버튼 클릭 횟수

private:
	Vector3 wheelStatus = Vector3(0, 0, 0); //xy : 마우스 커서의 위치, z : 휠값
	Vector3 wheelOldStatus = Vector3(0, 0, 0); //아래 변수(델타값)을 구하기 위한 제물
	Vector3 wheelMoveValue = Vector3(0, 0, 0); //이전 프레임과 현재 프레임의 델타 차이
};