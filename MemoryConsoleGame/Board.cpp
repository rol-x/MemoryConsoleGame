#include "Board.h"

void Board::loadCardsFromFile() // TODO: File doesn't exist exception
{
	fstream cardsFile;
	cardsFile.open("cards.txt", ios::in);
	try
	{
		vector<Card*> initialCardsVector;
		for (int i = 0; i < _boardSize*_boardSize / 2; i++)
		{
			if (!cardsFile.good())
				throw FileTooSmallException();
			string cardContent = "";
			cardsFile >> cardContent;
			Card * card = new Card(cardContent);
			initialCardsVector.push_back(card);
			initialCardsVector.push_back(new Card(cardContent));		// We push every card twice and then we shuffle the order
		}
		if (areCardsDoubled(initialCardsVector))
			throw DoubledCardException();

		for (int i = 0; i < _boardSize; i++)
		{
			vector<Card*> _row;
			for (int j = 0; j < _boardSize; j++)
			{
				shuffleVector(initialCardsVector);			// The vector is shuffled and each time the last element is pushed on the board
				_row.push_back(initialCardsVector.back());
				initialCardsVector.pop_back();
			}
			_cards.push_back(_row);
		}

	}
	catch (const FileLoadingException& exc)
	{
		cout << endl << exc.what() << endl;
		throw;
	}
}

bool Board::areCardsDoubled(vector<Card*> cards)
{
	map<string, int> contentCount;
	for (int i = 0; i < cards.size(); i++)
		if (contentCount.find(cards[i]->Content()) == contentCount.end())
			contentCount[cards[i]->Content()] = 1;
		else
			contentCount[cards[i]->Content()]++;
	for (int i = 0; i < cards.size(); i++)
		if (contentCount[cards[i]->Content()] > 2)
			return true;
	return false;
}

void Board::shuffleVector(vector<Card*>& cards)
{
	vector<Card*> shuffledVector;
	int randomIndex;
	int cardsCount = cards.size();
	for (int i = 0; i < cardsCount; i++)
	{
		randomIndex = rand() % cards.size();
		shuffledVector.push_back(cards[randomIndex]);
		cards.erase(cards.begin() + randomIndex);
	}
	cards = shuffledVector;
}

void Board::showProgress()
{
	cout << _progress << "/" << _boardSize * _boardSize / 2 << " pairs found" << endl;
}

void Board::showClock()
{
	time_t runTime = (clock() - _startTime) / CLOCKS_PER_SEC;
	int minutes = static_cast<int>(runTime) / 60;
	int seconds = static_cast<int>(runTime) % 60;
	cout << minutes << "m " << seconds << "s " << endl;
}

Board::Board(int boardSize)
{
	_startTime = clock();
	_boardSize = boardSize;
	try
	{
		loadCardsFromFile();
		_progress = 0;
	}
	catch (const FileLoadingException&)
	{
		throw;
	}
}

void Board::Show()
{
	system("cls");
	_console.RemoveScrollbar();
	for (char columnIndex = 'a'; columnIndex - 97 < _boardSize; columnIndex++)
		cout << "\t" << columnIndex << "\t\t";
	cout << endl << endl;

	int rowIndex = 1;
	for (auto cardRow : _cards)
	{
		cout << rowIndex++ << "\t";
		for (auto card : cardRow)
		{
			if (CardsRevealed() == 2 && card->IsRevealed())
			{
				if (DoRevealedCardsMatch())
					_console.SetTextColor(COLOR::GREEN);
				else
					_console.SetTextColor(COLOR::RED);
			}
			cout << card->Show() << "\t\t";
			_console.SetTextColor(COLOR::WHITE);
		}
		cout << endl << endl << endl;
	}

	cout << endl;
	showProgress();
	showClock();
}

void Board::ShowWithPause()
{
	Show();
	Sleep(2500);
}

pair<char, int> * Board::GetAddress()
{
	string address;
	cout << "\n\n\n\t\t\t\t\t\t\tWhich card do you want to reveal?\n\t\t\t\t\t\t\t> ";
	cin >> address;
	pair<char, int> * addressPair;
	if (address.length() != 2)
	{
		_console.ShiftCursor(0, -3);
		cout << "\t\t\t\t\t\t\tImproper address format!" << endl;
		_console.ClearCurrentLine();
		cout << "\t\t\t\t\t\t\t";
		return nullptr;
	}
	
	char first = address.at(0);
	char second = address.at(1);
	addressPair = new pair<char, int>();
	
	if (second >= '1' && second < '1' + _boardSize)		// digit is second
	{
		if (first >= 'a' && first < 'a' + _boardSize)		// lowercase letter is first
		{
			addressPair->first = first;
			addressPair->second = second - 48;
		}
		else if (first >= 'A' && first < 'A' + _boardSize)	// uppercase letter is first
		{
			addressPair->first = first;
			addressPair->second = second - 48;
		}
		else
		{
			_console.ShiftCursor(0, -3);
			cout << "\t\t\t\t\t\t\tInvalid address!" << endl;
			_console.ClearCurrentLine();
			cout << "\t\t\t\t\t\t\t";
			return nullptr;
		}
	}
	else if (first >= '1' && first < '1' + _boardSize)	// digit is first
	{
		if (second >= 'a' && second < 'a' + _boardSize)	// lowercase letter is second
		{
			addressPair->first = second;
			addressPair->second = first - 48;
		}
		else if (second >= 'A' && second < 'A' + _boardSize)	// uppercase letter is second
		{
			addressPair->first = second;
			addressPair->second = first - 48;
		}
		else
		{
			_console.ShiftCursor(0, -3);
			cout << "\t\t\t\t\t\t\tInvalid address!" << endl;
			_console.ClearCurrentLine();
			cout << "\t\t\t\t\t\t\t";
			return nullptr;
		}
	}
	else
	{
		_console.ShiftCursor(0, -3);
		cout << "\t\t\t\t\t\t\tInvalid address!" << endl;
		_console.ClearCurrentLine();
		cout << "\t\t\t\t\t\t\t";
		return nullptr;
	}
	return addressPair;
}

Card * Board::CardAtAddress(pair<char, int> * address)
{
	int row = address->second - 1;
	int column = 0;
	if (address->first >= 'a')
		column = static_cast<int>(address->first - 97);
	else
		column = static_cast<int>(address->first - 65);
	Card * card;
	try
	{
		if (row >= _boardSize || row < 0 || column >= _boardSize || column < 0)
			throw out_of_range("\nCard address out of range!\n");
		card = _cards[row][column];
	}
	catch (const exception& exc)
	{
		return nullptr;
	}
	return card;
}

void Board::RevealCard(pair<char, int>* address)
{
	if (address == nullptr)
		system("pause");
	else if (!CardAtAddress(address)->IsRevealed())
		CardAtAddress(address)->Reveal();
}

int Board::CardsRevealed()
{
	int cardsRevealed = 0;
	for (auto cardRow : _cards)
		for (auto card : cardRow)
			if (card->IsRevealed() && !card->IsOutOfTheGame())
				cardsRevealed++;
	return cardsRevealed;
}

bool Board::DoRevealedCardsMatch()
{
	vector<Card*> revealedCards;
	for (auto &cardRow : _cards)
		for (auto &card : cardRow)
			if (card->IsRevealed() && !card->IsOutOfTheGame())
				revealedCards.push_back(card);
	if (revealedCards[0]->Content() == revealedCards[1]->Content())
		return true;
	else
		return false;
}

void Board::AddToProgress()
{
	_progress++;
}

void Board::RemoveRevealedCards()
{
	vector<Card*> revealedCards;
	for (auto &cardRow : _cards)
		for (auto &card : cardRow)
			if (card->IsRevealed() && !card->IsOutOfTheGame())
				revealedCards.push_back(card);
	revealedCards[0]->RemoveFromTheGame();
	revealedCards[1]->RemoveFromTheGame();
}

void Board::HideRevealedCards()
{
	vector<Card*> revealedCards;
	for (auto &cardRow : _cards)
		for (auto &card : cardRow)
			if (card->IsRevealed() && !card->IsOutOfTheGame())
				revealedCards.push_back(card);
	revealedCards[0]->Hide();
	revealedCards[1]->Hide();
}

bool Board::AreAllCardsRemoved()
{
	for (auto cardRow : _cards)
		for (auto card : cardRow)
			if (!card->IsOutOfTheGame())
				return false;
	return true;
}

Board::~Board()
{
}
