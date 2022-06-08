#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
	for (Clip* clip : clips)
		SafeDelete(clip);
}

void Animation::Update()
{
	CheckTrue(currentClip < 0);

	clips[currentClip]->Position(position);
	clips[currentClip]->Scale(scale);
	clips[currentClip]->Rotation(rotation);
	
	clips[currentClip]->Update();
}

void Animation::Render()
{
	CheckTrue(currentClip < 0);

	clips[currentClip]->Render();
}

void Animation::AddClip(Clip* clip)
{
	clips.push_back(clip);
}

void Animation::Play(int clipIndex)
{
	CheckTrue(currentClip == clipIndex);

	if (currentClip > -1)
		clips[currentClip]->Stop();
	
	currentClip = clipIndex;
	clips[currentClip]->Play();
}

void Animation::Stop()
{
	CheckFalse(currentClip > -1);
	clips[currentClip]->Stop();
}

void Animation::Position(float x, float y)
{
	Position(Vector2(x, y));
}

void Animation::Position(Vector2& vec)
{
	position = vec;
}

void Animation::Scale(float x, float y)
{
	Scale(Vector2(x, y));
}

void Animation::Scale(Vector2& vec)
{
	scale = vec;
}

void Animation::Rotation(float x, float y, float z)
{
	Rotation(Vector3(x, y, z));
}

void Animation::Rotation(Vector3& vec)
{
	rotation = vec;
}

void Animation::RotationDegree(float x, float y, float z)
{
	RotationDegree(Vector3(x, y, z));
}

void Animation::RotationDegree(Vector3& vec)
{
	Vector3 temp;
	temp.x = Math::ToRadian(vec.x);
	temp.y = Math::ToRadian(vec.y);
	temp.z = Math::ToRadian(vec.z);

	Rotation(temp);
}

Vector3 Animation::RotationDegree()
{
	Vector3 temp = rotation;
	temp.x = Math::ToDegree(temp.x);
	temp.y = Math::ToDegree(temp.y);
	temp.z = Math::ToDegree(temp.z);

	return temp;
}

Vector2 Animation::ScaledTextureSize()
{
	assert(currentClip > -1);

	return clips[currentClip]->ScaledTextureSize();
}

Clip* Animation::GetCurrentClip()
{
	CheckTrueResult(currentClip < 0, nullptr);

	return clips[currentClip];
}

Sprite* Animation::GetCurrentFrameAsSprite()
{
	return GetCurrentClip()->GetCurrentFrameAsSprite();
}
