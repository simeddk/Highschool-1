#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Bullet.h"

Shader* shader = nullptr;
Sprite* marioSheet = nullptr;
Background_Mario* background = nullptr;

vector<Bullet*> bullets;
float delay = 0.01f;
float pressTime = 0.05f;


void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	background = new Background_Mario(shader);

	marioSheet = new Sprite(shader, L"MarioSheet.png", 70, 248, 117, 327);
	marioSheet->Position(700, 165);
	marioSheet->Scale(marioSheet->TextureSize());
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(marioSheet);
	SafeDelete(background);

	for (Bullet* bullet : bullets)
		SafeDelete(bullet);
}

void Update()
{
	//디버깅
	ImGui::LabelText("Bullet Count", "%d", bullets.size());
	ImGui::LabelText("FPS", "%.2f", ImGui::GetIO().Framerate);
	if (Key->Down('X'))
		bullets.clear();

	//마리오 이동
	Vector2 position = marioSheet->Position();

	if (Key->Press('D'))
		position.x += 200.0f * Time::Delta();
	else if (Key->Press('A'))
		position.x -= 200.0f * Time::Delta();

	if (Key->Press('W'))
		position.y += 200.0f * Time::Delta();
	else if (Key->Press('S'))
		position.y -= 200.0f * Time::Delta();

	marioSheet->Position(position);

	//총알 발사
	float angle = 0.0f;
	if (Key->Press(VK_SPACE))
	{
		pressTime += Time::Delta() / delay;

		if (pressTime >= 1.0f)
		{
			angle = Math::Lerp<float>(0.f, 360.f, fmodf(Time::Get()->Running(), 360.0f));
			bullets.push_back(new Bullet(shader, position, angle, 600.0f));
			pressTime = 0.0f;
		}
	}

	//객체 업데이트
	background->Update();
	marioSheet->Update();

	//총알 삭제 & 총알 업데이트
	vector<Bullet*>::iterator it = bullets.begin();
	for (it; it != bullets.end(); ++it)
	{
		Bullet* bullet = *it;
		bullet->Update();

		if ((bullet->Position().y > Height) || //Top
			(bullet->Position().x > Width) || //Right
			(bullet->Position().x < 0) || //Left
			(bullet->Position().y < 0) //Bottom
			)
		{
			bullets.erase(it);
			break;
		}
	}
}

void Render()
{
	background->Render();
	marioSheet->Render();

	for (Bullet* bullet : bullets)
		bullet->Render();
}