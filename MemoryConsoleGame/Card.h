#pragma once
#include <string>

using namespace std;

class Card
{
private:
	bool _isRevealed;
	bool _isOutOfTheGame;
	string _content;
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

