#include "Console.h"

void Console::SetConsoleSize(GAMEMODE mode)
{
	GetWindowRect(console, &ConsoleRect);
	switch (mode)
	{
	case EASY:
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 750, 410, TRUE);
		break;
	case MEDIUM:
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1100, 510, TRUE);
		break;
	case HARD:
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1450, 610, TRUE);
		break;
	default:
		break;
	}
}

void Console::ShiftCursor(int dx, int dy)
{
	GetConsoleScreenBufferInfo(hConsoleOutput, &consoleInfo);
	auto position = consoleInfo.dwCursorPosition;
	position.X += dx;
	position.Y += dy;
	SetConsoleCursorPosition(hConsoleOutput, position);
}

void Console::SetCursorPosition(int x, int y)
{
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsoleOutput, position);
}

POINT Console::GetCursorPosition()
{
	GetConsoleScreenBufferInfo(hConsoleOutput, &consoleInfo);
	auto pos = consoleInfo.dwCursorPosition;
	POINT position;
	position.x = pos.X;
	position.y = pos.Y;
	return position;
}

int Console::GetConsoleWidth()
{
	auto startingPosition = GetCursorPosition();
	SetCursorPosition(0, startingPosition.y);
	int width = 0;
	for (int i = 0; GetCursorPosition().y == startingPosition.y; i++)
	{
		std::cout << " ";
		width = i;
	}
	SetCursorPosition(startingPosition.x, startingPosition.y);
	return width;
}

void Console::SetTextColor(COLOR color)
{
	switch (color)
	{
	case GREEN:
		SetConsoleTextAttribute(hConsoleOutput, 10);
		break;
	case RED:
		SetConsoleTextAttribute(hConsoleOutput, 12);
		break;
	case WHITE:
		SetConsoleTextAttribute(hConsoleOutput, 15);
		break;
	case GOLD:
		SetConsoleTextAttribute(hConsoleOutput, 6);
		break;
	}
}

void Console::ClearCurrentLine()
{
	auto position = GetCursorPosition();
	SetCursorPosition(0, position.y);
	while (GetCursorPosition().y == position.y)
		std::cout << " ";
	SetCursorPosition(position.x, position.y);
}

void Console::RemoveScrollbar() // TODO: Everywhere
{
	ShowScrollBar(console, SB_BOTH, false);
}

void Console::DisableResizing()
{
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

Console::Console()
{
}


Console::~Console()
{
}
