/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 07/10/2019
/// </summary>

#include "Game.h"


Game::Game() :
	m_gamePlaying{ false },
	m_input{ 0 },
	m_player{ nullptr },
	m_enemy{ nullptr },
	m_playersItems{ 0, 0 }
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
	m_playersItems.potions = 4;
	pickRace();
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
		combat();
		update();
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
	std::cout << "Enter a number in the range 0 - " << t_inputRange << ": ";
	std::cin >> m_input;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(CIN_LIMIT, '\n');
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

/// <summary>
/// Lets the user select a race. Sets the other race as an enemy
/// </summary>
void Game::pickRace()
{
	while (!getInput("Choose your race:\n1 = Orc\n2 = Troll\n", 2));
	{
		if (m_input == 1)
		{
			m_player = &m_orc;
			m_enemy = &m_troll;
			std::cout << "You chose orc" << std::endl;
			m_player->printStats();
			system("pause");
		}
		else if (m_input == 2)
		{
			m_player = &m_troll;
			m_enemy = &m_orc;
			std::cout << "You chose troll" << std::endl;
			m_player->printStats();
			system("pause");
		}
	}
}

/// <summary>
/// Takes input from the player for attack type and checks if you dealth or took damage
/// </summary>
void Game::combat()
{
	displayCombatStats();

	// Get input on attack
	getInput("Choose your attack:\n1 = Magic\n2 = Melee\n3 = Defence (Counter attack)\n4 = Take potion\n", 4);

	Attack enemyAttack = static_cast<Attack>(rand() % 3);

	switch (m_input)
	{
	case 1: // Magic attack
		if (enemyAttack == Attack::Defence) // Magic > Defence, check if attack is sucessful
		{
			m_enemy->damage(m_player->attack(Attack::Magic));
			std::cout << "You did " << m_player->attack(Attack::Magic) << " damage."<< std::endl;
		}
		else if (enemyAttack == Attack::Melee)
		{
			m_player->damage(m_enemy->attack(enemyAttack));
			std::cout << "You took " << m_enemy->attack(enemyAttack) << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
		
		break;
	case 2: // Melee attack
		if (enemyAttack == Attack::Magic)
		{
			m_enemy->damage(m_player->attack(Attack::Melee));
			std::cout << "You did " << m_player->attack(Attack::Melee) << " damage." << std::endl;
		}
		else if (enemyAttack == Attack::Defence)
		{
			m_player->damage(m_enemy->attack(enemyAttack));
			std::cout << "You took " << m_enemy->attack(enemyAttack) << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
		
		break;
	case 3: // Counter attack (Defence)
		if (enemyAttack == Attack::Melee)
		{
			m_enemy->damage(m_player->attack(Attack::Defence));
			std::cout << "You did " << m_player->attack(Attack::Defence) << " damage." << std::endl;
		}
		else if (enemyAttack == Attack::Magic)
		{
			m_player->damage(m_enemy->attack(Attack::Magic));
			std::cout << "You took " << m_enemy->attack(Attack::Magic) << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
		
		break;
	case 4: // Take potion
		if (m_playersItems.potions > 0)
		{
			m_playersItems.potions--;
			int healAmount = m_player->takePotion();
			std::cout << "You used a potion! " << healAmount << " health restored." << std::endl;
		}
		break;
	}

	displayCombatStats();
	system("pause");
}

/// <summary>
/// Displays the combat statistics.
/// <para>Displays the player and enemy health and race</para>
/// </summary>
void Game::displayCombatStats()
{
	// Display player and enemy statistics
	COORD lastCursorPosition = GetConsoleCursorPosition(hConsole); // Get the current cursor position

	SetConsoleCursorPosition(hConsole, { 60, 0 }); // Set the cursor position
	std::cout << "Player: " << "\t|\tEnemy: "; // Output the player and enemy header

	SetConsoleCursorPosition(hConsole, { 60, 1 }); // Set the cursor position
	std::cout << "Race: " << m_player->getRace() << "\t|\tRace: " << m_enemy->getRace(); // Output the player and enemy race

	SetConsoleCursorPosition(hConsole, { 60, 2 }); // Set the cursor position
	std::cout << "Health: " << m_player->getHealth() << " \t|\tHealth: " << m_enemy->getHealth() << "   "; // Output the player and enemy health

	SetConsoleCursorPosition(hConsole, { 60, 3 }); // Set the cursor position
	std::cout << "Potions: " << m_playersItems.potions << "\t|"; // Output the player's potions

	SetConsoleCursorPosition(hConsole, lastCursorPosition); // Set the cursor back to the previous position
}

/// <summary>
/// Updates the game.
/// <para>Checks if the player has died, ends the game if they have.</para>
/// <para>Checks if the enemy has died, spawns new one if they have</para>
/// </summary>
void Game::update()
{
	if (m_player->getHealth() <= 0)
	{
		system("cls");
		std::cout << "You died!" << std::endl;
		m_gamePlaying = false;
		system("pause");
	}

	if (m_enemy->getHealth() <= 0)
	{
		std::cout << "You have slain the enemy!" << std::endl;
		system("pause");
		m_enemy->setStats();
	}
}

/// <summary>
/// Returns the console cursor position in coordinates
/// </summary>
/// <param name="hConsoleOutput">Console handle</param>
/// <returns>Cursor coordinates</returns>
COORD Game::GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}