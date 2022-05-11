#pragma once

enum class EPlayType { OnceAndLastFrame, OnceAndFirstFrame,Loop };

struct Frame
{
	Sprite* Image;	//������ �׸�(��������Ʈ)
	float Time;		//�� ������ ������ �ð�

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
	float speed = 1.0f;			//���
	float length = 0.0f;		//��ü ����
	float playTime = 0.0f;		//Ÿ�̸�(°��°��...)

	UINT currentFrame = 0;		//���� ��� ���� ������ ��ȣ
	bool bPlaying = false;		//���������..

	EPlayType playType;			//�ݺ�����Ұ���, �ѹ��� ����Ұ���
	vector<Frame*> frames;		//�����ӵ��� ����

	Vector2 position = Vector2(0, 0);
	Vector2 scale = Vector2(1, 1);
};