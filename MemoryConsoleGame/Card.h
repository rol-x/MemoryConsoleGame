#pragma once
#include "Container.h"

using namespace std;

class Card : public Container
{
private:
	string _content;
	bool _isRevealed;
	bool _isOutOfTheGame;
public:
	Card(string content);
	string Show();
	string Content();
	void Reveal();
	void Hide();
	bool IsRevealed();
	bool IsOutOfTheGame();
	void RemoveFromTheGame();
	~Card();
};

