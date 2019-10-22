#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	auto * game = new Game();
	game->Run();
	return 0;
}