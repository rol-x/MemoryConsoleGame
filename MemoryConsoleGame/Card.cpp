#include "Card.h"



Card::Card(string content)
{
	_content = content;
	_isRevealed = false;
	_address = "a1";			// Address management
}

string Card::Show()
{
	if (_isRevealed)
		return _content;
	else
		return "XXXXXXX";
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


Card::~Card()
{
}
