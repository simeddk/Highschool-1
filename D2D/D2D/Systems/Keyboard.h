#pragma once

#define MAX_KEY_INPUT 256

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool Down(int key);
	bool Up(int key);
	bool Press(int key);
	bool Toggle(int key);

private:
	bitset<MAX_KEY_INPUT> up;
	bitset<MAX_KEY_INPUT> down;
};