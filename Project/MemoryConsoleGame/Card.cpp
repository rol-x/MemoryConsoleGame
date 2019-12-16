#include "Card.h"



Card::Card(string content)
{
	_content = content;
	_isRevealed = false;
	_isOutOfTheGame = false;
}

string Card::Show()
{
	if (_isRevealed)
		return Display(_content);
	else
		return Display("XXXXXXXXXXXXXXX");
}

string Card::Content()
{
	return _content;
}

void Card::Reveal()
{
	_isRevealed = true;
}

void Card::Hide()
{
	_isRevealed = false;
}

bool Card::IsRevealed()
{
	return _isRevealed;
}

bool Card::IsOutOfTheGame()
{
	return _isOutOfTheGame;
}

void Card::RemoveFromTheGame()
{
	_isOutOfTheGame = true;
}

Card::~Card()
{
}
