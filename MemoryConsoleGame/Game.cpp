#include "Game.h"

void Game::finishGame()
{
	_isGameRunning = false;
	_isGameFinished = true;
}

void Game::showEndingScreen()
{
	cout << "You finished the game!" << endl;
	system("pause");
}

Game::Game()
{
	srand(time(0));
	Console().RemoveScrollbar();
	Console().SetTextColor(COLOR::WHITE);
	_isGameRunning = true;
	_isGameFinished = false;
	ShowMenu();
}

void Game::ShowMenu()
{
	try
	{
		bool showMenu = true;
		while (showMenu)
		{
			system("cls");
			cout << endl;
			cout << "Welcome to Memory Game - Console Version!\n\nChoose the level of difficulty:\n[E] Easy\n[M] Medium\n[H] Hard\n\n[Q] Quit\n";
			switch (_getch())
			{
			case 'E':
			case 'e':
				_board = new Board(4);
				_console.SetConsoleSize(GAMEMODE::EASY);
				showMenu = false;
				break;
			case 'M':
			case 'm':
				_board = new Board(6);
				_console.SetConsoleSize(GAMEMODE::MEDIUM);
				showMenu = false;
				break;
			case 'H':
			case 'h':
				_board = new Board(8);
				_console.SetConsoleSize(GAMEMODE::HARD);
				showMenu = false;
				break;
			case 'Q':
			case 'q':
				showMenu = QuitPrompt();
				break;
			}
		}
	}
	catch (const FileLoadingException exc) // Intentional slicing
	{
		cout << exc.what() << endl << endl;
		_isGameRunning = false;
		system("pause");
	}
}

bool Game::QuitPrompt()
{
	bool showQuitPrompt = true;
	while (showQuitPrompt)
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tAre you sure to quit?\n\n\t\t\t\t\t       [Q] Quit   [Esc] Cancel\n";
		switch (_getch())
		{
		case 'Q':
		case 'q':
			showQuitPrompt = false;
			_isGameRunning = false;
			return false;
			break;
		case 27:
			showQuitPrompt = false;
			return true;
			break;
		default:
			break;
		}
	}
}

void Game::Run()
{
	pair<char, int> * cardAddressToReveal;
	while (_isGameRunning)
	{
		_board->Show();
		cardAddressToReveal = _board->GetAddress(); // redone
		_board->RevealCard(cardAddressToReveal);
		if (_board->CardsRevealed() < 2)
			continue;
		if (_board->CardsRevealed() == 2 && _board->DoRevealedCardsMatch())
		{
			_board->AddToProgress();
			_board->ShowWithPause();
			_board->RemoveRevealedCards();
		}
		else
		{
			_board->ShowWithPause();
			_board->HideRevealedCards();
		}
		if (_board->AreAllCardsRemoved())
			finishGame();
	}
	if (_isGameFinished)
		showEndingScreen();
}

Game::~Game()
{
}