#pragma once
#include "Board.h"

class Game
{
private:
	bool _isGameRunning;
	bool _isGameFinished;
	Board * _board = nullptr;
	void finishGame();
	void showEndingScreen();
public:
	Game();
	void ShowMenu();
	bool QuitPrompt();
	void Run();
	~Game();
};

