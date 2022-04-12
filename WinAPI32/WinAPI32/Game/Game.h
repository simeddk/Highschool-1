#pragma once

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

private:
	class Player* player;
};
