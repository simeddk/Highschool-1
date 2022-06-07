#include "stdafx.h"
#include "S11_SoundDemo.h"
#include "Objects/Marco.h"

S11_SoundDemo::S11_SoundDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	
	marco = new Marco(shader, Vector2(0, 0), Vector2(1, 1));
	marco->Position(Vector2(0, -170.0f));
	Context::Get()->SetFollowMode(marco);

	images[0] = new Sprite(shader, L"Cover/ff6.png");
	images[0]->Scale(Vector2(0.2f, 0.2f));
	images[0]->Position(Vector2(-300, 0));

	images[1] = new Sprite(shader, L"Cover/ff7.jpg");
	images[1]->Scale(Vector2(0.35f, 0.35f));
	images[1]->Position(Vector2(0, 0));

	images[2] = new Sprite(shader, L"Cover/aimtotop2.jpeg");
	images[2]->Scale(Vector2(0.65f, 0.65f));
	images[2]->Position(Vector2(300, 0));

	//TODO 01. mid는 스트림 생성이 안되네..
	//Sound->AddSound(names[0], L"terra.mid", true);
	//Sound->AddSound(names[1], L"prelude.mid", true);
	Sound->AddSound(names[2], L"(Track 28).mp3", true);
	Sound->AddSound(L"Click", L"click.wav");
}

S11_SoundDemo::~S11_SoundDemo()
{
	SafeDelete(shader);

	SafeDelete(marco);

	for (Sprite* image : images)
		SafeDelete(image);
}

void S11_SoundDemo::Update()
{
	//TODO 02. 볼륨도 조절할 것
	if (Mouse->Down(LButton) || Mouse->Down(RButton))
		Sound->Play(names[2], 0.2f);

	for (Sprite* image : images)
		image->Update();

	marco->Update();
}

void S11_SoundDemo::Render()
{
	for (Sprite* image : images)
		image->Render();

	marco->Render();
}
