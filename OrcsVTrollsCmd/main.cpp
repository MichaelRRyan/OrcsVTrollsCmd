/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// @Time 12:32
/// </summary>

#include <ctime>
#include "Game.h"

int main()
{
	// Set the seed for randomisation
	srand(static_cast<unsigned>(time(nullptr)));

	// Create an object for the game and start
	Game game;
	game.startGame();

	return EXIT_SUCCESS;
}