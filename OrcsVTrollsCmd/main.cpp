/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// @Time 12:32
/// </summary>

#include <ctime>
#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	Game game;
	game.startGame();

	return EXIT_SUCCESS;
}