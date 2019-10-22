#include "Game.h"



Game::Game()
{
	_isGameRunning = true;
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
			cout << "\n\t\t\t\t\tWelcome to Memory Game - Console Version!\n\nChoose the level of difficulty:\n[E] Easy\n[M] Medium\n[H] Hard\n\n[Q] Quit\n";
			switch (_getch())
			{
			case 'E':
			case 'e':
				_board = new Board(4);
				showMenu = false;
				break;
			case 'M':
			case 'm':
				_board = new Board(5);
				showMenu = false;
				break;
			case 'H':
			case 'h':
				_board = new Board(6);
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
	pair<char, int> * revealedCardAddress;
	while (_isGameRunning)
	{
		_board->Show();
		revealedCardAddress = _board->GetAddress();
		_board->RevealCard(revealedCardAddress);
	}
}

Game::~Game()
{
}
