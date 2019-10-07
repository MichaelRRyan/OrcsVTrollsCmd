/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 07/10/2019
/// </summary>

#include "Game.h"


Game::Game() :
	m_gamePlaying{ false },
	m_input{ 0 }
{
	
}

/// <summary>
/// Starts the game.
/// <para>Sets the gameplay bool to true.</para>
/// <para>Calls the update gameloop function.</para>
/// </summary>
void Game::startGame()
{
	//std::cout << "Let go virtual" << std::endl;
	///*Character character;
	//character.flip();
	//character.walk();*/

	//std::cout << "Let go create an Orc" << std::endl;
	//Orc orc;
	//orc.walk();
	//orc.fly();
	//orc.flip();

	//std::cout << "Let go create an Troll" << std::endl;
	//Troll troll;
	//troll.walk();
	//troll.fly();
	//troll.flip();

	//Character* npc = &orc;
	//npc->flip();
	//npc->fly();
	//npc->walk();

	//std::cout << "Orc" << std::endl;
	//npc->printStats();

	//npc = &troll;
	//npc->flip();
	//npc->fly();
	//npc->walk();

	//std::cout << "Troll" << std::endl;
	//npc->printStats();



	m_gamePlaying = true;
	gameLoop();

	system("pause");
}

/// <summary>
/// Main game gameloop
/// <para>Calls all the other functions in order</para>
/// </summary>
void Game::gameLoop()
{
	while (m_gamePlaying)
	{
		getInput();
	}
}

/// <summary>
/// Takes input from the player.
/// <para>Disgregards the input if it is not a valid input.</para>
/// </summary>
void Game::getInput()
{
	std::cout << "Enter 0 to exit game: ";
	std::cin >> m_input;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Unrecognised input type." << std::endl;
	}
	else if (m_input == 0)
	{
		m_gamePlaying = false;
	}
}
