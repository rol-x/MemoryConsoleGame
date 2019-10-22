#include "Board.h"



void Board::loadCardsFromFile() // File doesn't exist exception
{
	fstream cardsFile;
	cardsFile.open("cards.txt", ios::in);
	try
	{
		for (int i = 0; i < _boardSize; i++)
		{
			vector<Card*> _row;
			for (int j = 0; j < _boardSize; j++)
			{
				if (!cardsFile.good())
					throw FileTooSmallException();
				string cardContent = "";
				cardsFile >> cardContent;
				Card * card = new Card(cardContent);
				_row.push_back(card);
			}
			_cards.push_back(_row);
		}
		if (areDoubles(_cards))
			throw DoubledCardException();
	}
	catch (const FileLoadingException& exc)
	{
		cout << endl << exc.what() << endl;
		throw;
	}
}

bool Board::areDoubles(vector<vector<Card*>> cards)
{
	return false;
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
}

void Board::Show()
{
	system("cls");

	for (char columnIndex = 'a'; columnIndex - 97 < _boardSize; columnIndex++)
		cout << "\t" << columnIndex << "\t\t";
	cout << endl;

	int rowIndex = 1;
	for (auto cardRow : _cards)
	{
		cout << rowIndex++ << "\t";
		for (auto card : cardRow)
		{
			cout << card->Show() << "\t\t";
		}
		cout << endl;
	}
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

Board::~Board()
{
}
