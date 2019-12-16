#pragma once
#include "Board.h"
#include "Console.h"

class Game
{
private:
	Console _console;
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

