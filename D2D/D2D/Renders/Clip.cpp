#include "stdafx.h"
#include "Clip.h"

//-----------------------------------------------------------------------------
//Frame
//-----------------------------------------------------------------------------
Frame::Frame(Sprite* sprite, float time)
	: Image(sprite)
	, Time(time)
{
}

Frame::~Frame()
{
	SafeDelete(Image);
}

//-----------------------------------------------------------------------------
//Clip
//-----------------------------------------------------------------------------
Clip::Clip(EPlayType playType, float speed)
	: playType(playType)
	, speed(speed)
{
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		SafeDelete(frame);
}

void Clip::Update()
{
	Frame* frame = frames[currentFrame];

	if (bPlaying == true)
	{
		float keepTime = frame->Time / speed; //�� �������� ������ �ð�
		playTime += Time::Delta(); //Ÿ�̸�

		//Ÿ�̸Ӱ� �� �������� ������ �ð��� ����ϸ� -> ���� ���������� �Ѿ�� ��
		if (playTime >= keepTime)
		{
			//���� ���������� �Ѿ��
			switch (playType)
			{
				//�ѹ� ����� ���, �÷��� ����
				case EPlayType::OnceAndLastFrame:
				case EPlayType::OnceAndFirstFrame:
				{
					currentFrame++;
					if (currentFrame >= frames.size())
						Stop();
				}
				break;

				//������ ���, ������ ����Ǹ� �ٽ� 0���������� ���ƿ���
				case EPlayType::Loop:
				{
					currentFrame++;
					currentFrame %= frames.size();
				}
				break;
			}//swith

			playTime = 0.0f;
			
		}//if(playTime)
	} //if(bPlaying)

	frames[currentFrame]->Image->Position(position);
	frames[currentFrame]->Image->Scale(scale);

	frames[currentFrame]->Image->Update();
}

void Clip::Render()
{
	frames[currentFrame]->Image->Render();
}

void Clip::AddFrame(Sprite* sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	bPlaying = true;
	currentFrame = 0;
	playTime = 0.0f;
}

void Clip::Play(UINT startFrame)
{
	bPlaying = true;
	currentFrame = startFrame;
	playTime = 0.0f;
}

void Clip::Stop()
{
	bPlaying = false;

	switch (playType)
	{
		case EPlayType::OnceAndLastFrame:
		{
			currentFrame = frames.size() - 1;
		}
		break;
		
		case EPlayType::OnceAndFirstFrame:
		{
			currentFrame = 0;
		}
		break;
	}
}

void Clip::Speed(float val)
{
	speed = val;
}

Sprite* Clip::GetCurrentFrameAsSprite()
{
	return frames[currentFrame]->Image;
}

Vector2 Clip::ScaledTextureSize()
{
	return GetCurrentFrameAsSprite()->ScaledTextureSize();
}

void Clip::Position(float x, float y)
{
	Position(Vector2(x, y));
}

void Clip::Position(Vector2& vec)
{
	position = vec;
}

void Clip::Scale(float x, float y)
{
	Scale(Vector2(x, y));
}

void Clip::Scale(Vector2& vec)
{
	scale = vec;
}
