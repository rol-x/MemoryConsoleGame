#pragma once
#include <windows.h>
#include <iostream>

enum GAMEMODE
{
	EASY,
	MEDIUM,
	HARD
};

enum COLOR
{
	GREEN,
	RED,
	WHITE
};

class Console
{
	HWND console = GetConsoleWindow();
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	RECT ConsoleRect;
public:
	void SetConsoleSize(GAMEMODE mode);
	void ShiftCursor(int dx, int dy);
	void SetCursorPosition(int x, int y);
	POINT GetCursorPosition();
	void SetTextColor(COLOR color);
	void ClearCurrentLine();
	void RemoveScrollbar();
	Console();
	~Console();
};

