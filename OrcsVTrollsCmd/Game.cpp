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
	m_gamePlaying = true;
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

	while (!getInput("Choose your race:\n1 = Orc\n2 = Troll\n", 2));
	{
		if (m_input == 1)
		{
			m_player = &m_orc;
			m_enemy = &m_troll;
			std::cout << "You chose orc" << std::endl;
			system("pause");
		}
		else if (m_input == 2)
		{
			m_player = &m_troll;
			m_enemy = &m_orc;
			std::cout << "You chose troll" << std::endl;
			system("pause");
		}
	} 

	
	gameLoop();
}

/// <summary>
/// Main game gameloop
/// <para>Calls all the other functions in order</para>
/// </summary>
void Game::gameLoop()
{
	while (m_gamePlaying)
	{
		// Exit game option
		system("cls");
		getInput("Enter a number: ", 0);
		if (m_input == 0)
		{
			m_gamePlaying = false;
		}

		combat();
	}
}

/// <summary>
/// Takes player inputs and returns true if done so successfully.
/// <para>Displays an error message and returns false if:</para> 
/// <para>- The player enters a string or character.</para>
/// <para>- The player enters a number less than 0 or outside the range.</para>
/// <para>Ends the game loop if the input is 0.</para>
/// </summary>
/// <param name="t_inputMessage">Message to display for input</param>
/// <param name="t_inputRange">The range of values that can be entered</param>
/// <returns>Whether the input was taken successfully</returns>
bool Game::getInput(const std::string t_inputMessage, const int t_inputRange)
{
	std::cout << "Entering 0 at any point will exit the game." << std::endl;
	std::cout << t_inputMessage;
	std::cin >> m_input;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Unrecognised input type." << std::endl;
		system("pause");
		system("cls");
		return false;
	}
	else if (m_input < 0 || m_input > t_inputRange)
	{
		std::cout << "Value outside of range. Enter a value within the range 0 to " << t_inputRange << "." << std::endl;
		system("pause");
		system("cls");
		return false;
	}
	else if (m_input == 0)
	{
		system("cls");
		std::cout << "Goodbye!" << std::endl;
		m_gamePlaying = false;
		system("pause");
	}

	return true;
}

void Game::combat()
{
	getInput("Enter a number: ", 0);
}
