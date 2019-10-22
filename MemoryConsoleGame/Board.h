#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <utility>
#include <Windows.h>
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
	bool areDoubles(vector<Card*> cards);
	void shuffleVector(vector<Card*>& cards);
	int _progress;
	void showProgress();
public:
	Board(int boardSize);
	void Show();
	void ShowWithPause();
	pair<char, int> * GetAddress();
	Card * CardAtAddress(pair<char, int> * address);
	void RevealCard(pair<char, int> * address);
	int CardsRevealed();
	bool RevealedCardsMatch();
	void AddToProgress();
	void RemoveRevealedCards();
	void HideRevealedCards();
	bool AllCardsAreRemoved();
	~Board();
};

