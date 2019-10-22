#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <utility>
#include "Card.h"
#include "FileTooSmallException.h"
#include "DoubledCardException.h"
#include "FileLoadingException.h"

using namespace std;

class Board
{
private:
	vector<vector<Card*>> _cards;
	int _boardSize;
	void loadCardsFromFile();
	bool areDoubles(vector<vector<Card*>> cards);
public:
	Board(int boardSize);
	void Show();
	pair<char, int> * GetAddress();
	Card * CardAtAddress(pair<char, int> * address);
	void RevealCard(pair<char, int> * address);
	~Board();
};

