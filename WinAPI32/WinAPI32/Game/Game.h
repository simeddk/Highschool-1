#pragma once

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

	void SetCursorPosition(POINT cursor) { cursorPosition = cursor; }

private:
	class Player* player;
	class Bullet* bullet;

	int score;
	int level;

	POINT cursorPosition;
};
