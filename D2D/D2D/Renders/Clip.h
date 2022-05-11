#pragma once

enum class EPlayType { OnceAndLastFrame, OnceAndFirstFrame,Loop };

struct Frame
{
	Sprite* Image;	//한장의 그림(스프라이트)
	float Time;		//이 한장을 유지할 시간

	Frame(Sprite* sprite, float time);
	~Frame();
};

class Clip
{
public:
	Clip(EPlayType playType = EPlayType::OnceAndLastFrame, float speed = 1.0f);
	~Clip();

	void Update();
	void Render();

public:
	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Speed(float val);

public:
	void Position(float x, float y);
	void Position(Vector2& vec);

	void Scale(float x, float y);
	void Scale(Vector2& vec);

private:
	float speed = 1.0f;			//배속
	float length = 0.0f;		//전체 길이
	float playTime = 0.0f;		//타이머(째깍째깍...)

	UINT currentFrame = 0;		//현재 재생 중인 프레임 번호
	bool bPlaying = false;		//재생중인지..

	EPlayType playType;			//반복재생할건지, 한번만 재생할건지
	vector<Frame*> frames;		//프레임들의 집합

	Vector2 position = Vector2(0, 0);
	Vector2 scale = Vector2(1, 1);
};