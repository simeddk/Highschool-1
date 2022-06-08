#pragma once

class Background_Mario
{
public:
	Background_Mario(Shader* shader);
	~Background_Mario();

	void Update();
	void Render();

private:
	Sprite* cloud[2];
	Sprite* bush[2];
	Sprite* tile;
};