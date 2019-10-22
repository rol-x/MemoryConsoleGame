#pragma once
#include "Board.h"
#include <conio.h>

class Game
{
private:
	bool _isGameRunning;
	Board * _board = nullptr;
public:
	Game();
	void ShowMenu();
	bool QuitPrompt();
	void Run();
	~Game();
};

