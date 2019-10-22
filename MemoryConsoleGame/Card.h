#pragma once
#include <string>

using namespace std;

class Card
{
private:
	bool _isRevealed;
	string _content;
	string _address;
public:
	Card(string content);
	string Show();
	void Reveal();
	void Hide();
	bool IsRevealed();
	~Card();
};

