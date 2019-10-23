#include "Board.h"



void Board::loadCardsFromFile() // File doesn't exist exception
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
		if (areDoubles(initialCardsVector))
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

bool Board::areDoubles(vector<Card*> cards)
{
	// TODO
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

Board::Board(int boardSize)
{
	_boardSize = boardSize;
	try
	{
		loadCardsFromFile();
	}
	catch (const FileLoadingException&)
	{
		throw;
	}
	_progress = 0;
}

void Board::Show()
{
	system("cls");

	for (char columnIndex = 'a'; columnIndex - 97 < _boardSize; columnIndex++)
		cout << "\t\t" << columnIndex << "\t";
	cout << endl;

	int rowIndex = 1;
	for (auto cardRow : _cards)
	{
		cout << rowIndex++ << "\t\t";
		for (auto card : cardRow)
		{
			cout << card->Show() << "\t\t\t";
		}
		cout << endl << endl;
	}

	cout << endl;
	showProgress();
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
		cout << "\t\t\t\t\t\t\tImproper address format!" << endl;
		return nullptr;
	}
	if (address.at(0) > 48 && address.at(0) <= 48 + _boardSize && address.at(1) > 96 && address.at(1) <= 96 + _boardSize)
	{
		addressPair = new pair<char, int>();
		addressPair->first = address.at(1);
		addressPair->second = address.at(0) - 48;
	}
	else if (address.at(1) > 48 && address.at(1) <= 48 + _boardSize && address.at(0) > 96 && address.at(0) <= 96 + _boardSize)
	{
		addressPair = new pair<char, int>();
		addressPair->first = address.at(0);
		addressPair->second = address.at(1) - 48;
	}
	else
	{
		cout << "\t\t\t\t\t\t\tInvalid address!" << endl;
		return nullptr;
	}
	return addressPair;
}

Card * Board::CardAtAddress(pair<char, int> * address)
{
	int row = address->second - 1;
	int column = static_cast<int>(address->first - 97);
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
	{
		cout << "\n\n\n\n\n";
		system("pause");
	}
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

bool Board::RevealedCardsMatch()
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

bool Board::AllCardsAreRemoved()
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
