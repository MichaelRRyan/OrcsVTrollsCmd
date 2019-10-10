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
	m_playerGear{},
	m_roundNumber{ 1 }
{
	m_shopText = "1 = Exit Shop\n";

	for (int i = 0; i < NO_OF_ITEMS; i++)
	{
		if (i == 0)
		{
			m_shopText.append("- Spells:\n");
		}
		else if (i == 5)
		{
			m_shopText.append("- Melee - Standard:\n");
		}
		else if (i == 9)
		{
			m_shopText.append("- Melee - Counter:\n");
		}
		else if (i == 12)
		{
			m_shopText.append("- Shields:\n");
		}

		m_shopText.append(std::to_string(i + 2) + " = " + ITEM_NAMES[i] + " | Price: " + std::to_string(ITEM_DAMAGES[i] * 10) + "\n");
	}

	m_shopText.append("17 = Potion | Price: 15\n");
}

/// <summary>
/// Starts the game.
/// <para>Sets the gameplay bool to true.</para>
/// <para>Calls the update gameloop function.</para>
/// </summary>
void Game::startGame()
{
	// Setup the player
	m_playerGear.m_gold = 30;
	m_playerGear.m_potions = 3;
	m_playerGear.m_Equiped = nullptr;

	for (int i = 0; i < m_playerGear.MAX_ITEMS; i++)
	{
		m_playerGear.m_inventory[0] = nullptr;
	}

	m_gamePlaying = true;

	std::cout << "The great war has ended, but both the Orcs and Trolls are still battling for control of the kingdom." << std::endl
		<< "Since the peace treaty was signed, and the war came to an end, the people of the kingdom decided to settle the battle" << std::endl
		<< "for control of the kingdom by a gladiator tournament! You, a famed and skilled fighter, now must go forth and battle" << std::endl
		<< "for your kingdom..." << std::endl;
	system("pause");
	system("cls");

	pickRace();
	shop();
	system("cls");
	std::cout << "Get ready, people! Round " << m_roundNumber << " is about to start!" << std::endl;
	system("pause");
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
	std::cout << "Orcs specialise in Magic (Wisdom, or WIS) and counter attacks (Dexterity, or DEX)." << std::endl
		<< "Trolls specialise in melee attacks (Strength, or STR) and are very tough to kill (Health, based on Constitution, or CON)" << std::endl <<std::endl;
	while (!getInput("Choose your race:\n1 = Orc\n2 = Troll\n", 2)); // Loop until a valid input is given

	if (m_input == 1)
	{
		m_player = &m_orc;
		m_enemy = &m_troll;
		std::cout << "You chose orc" << std::endl << std::endl << "Your stats: " << std::endl;
		m_player->printStats();
		system("pause");
	}
	else if (m_input == 2)
	{
		m_player = &m_troll;
		m_enemy = &m_orc;
		std::cout << "You chose troll" << std::endl << std::endl << "Your stats: " << std::endl;
		m_player->printStats();
		system("pause");
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
		magicAttack(enemyAttack);
		break;
	case 2: // Melee attack
		meleeAttack(enemyAttack);
		break;
	case 3: // Counter attack (Defence)
		counterAttack(enemyAttack);
		break;
	case 4: // Take potion
		if (m_playerGear.m_potions > 0)
		{
			m_playerGear.m_potions--;
			int healAmount = m_player->takePotion();
			std::cout << "You used a potion! " << healAmount << " health restored." << std::endl;
		}
		break;
	}

	displayCombatStats();
	system("pause");
}

/// <summary>
/// Function that handles player melee attack
/// </summary>
/// <param name="t_enemyAttack">The enemy's attack</param>
void Game::meleeAttack(Attack t_enemyAttack)
{
	if (checkForWeapon(ItemType::Melee))
	{
		if (t_enemyAttack == Attack::Magic)
		{
			int damageDone = m_player->attack(Attack::Melee) + (*m_playerGear.m_Equiped)->damage();
			m_enemy->damage(damageDone);
			std::cout << "You hit the enemy! You did " << damageDone << " damage." << std::endl;
		}
		else if (t_enemyAttack == Attack::Defence)
		{
			system("cls");
			std::cout << "Attack missed!" << std::endl;

			int damageDone = m_enemy->attack(t_enemyAttack);

			if (checkForWeapon(ItemType::Shield))
			{
				damageDone -= (*m_playerGear.m_Equiped)->damage();
				std::cout << "Attack successfully blocked! You soften the blow." << std::endl;
			}
			else
			{
				std::cout << "Selected item is not a shield" << std::endl;
			}

			m_player->damage(damageDone);
			std::cout << "You took " << damageDone << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
	}
	else
	{
		std::cout << "Weapon does not match attack type" << std::endl;
	}
}

/// <summary>
/// Function that handles player magic attack
/// </summary>
/// <param name="t_enemyAttack">The enemy's attack</param>
void Game::magicAttack(Attack t_enemyAttack)
{
	if (checkForWeapon(ItemType::Spell))
	{
		if (t_enemyAttack == Attack::Defence) // Magic > Defence, check if attack is sucessful
		{
			int damageDone = m_player->attack(Attack::Magic) + (*m_playerGear.m_Equiped)->damage();
			m_enemy->damage(damageDone);
			std::cout << "Spell hit! You did " << damageDone << " damage." << std::endl;
		}
		else if (t_enemyAttack == Attack::Melee)
		{
			system("cls");
			std::cout << "Spell missed!" << std::endl;

			int damageDone = m_enemy->attack(t_enemyAttack);

			if (checkForWeapon(ItemType::Shield))
			{
				damageDone -= (*m_playerGear.m_Equiped)->damage();
				std::cout << "Attack successfully blocked! You soften the blow." << std::endl;
			}
			else
			{
				std::cout << "Selected item is not a shield" << std::endl;
			}

			m_player->damage(damageDone);
			std::cout << "You took " << damageDone << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
	}
	else
	{
		std::cout << "Weapon does not match attack type" << std::endl;
	}
}

/// <summary>
/// Function that handles player counter attack
/// </summary>
/// <param name="t_enemyAttack">The enemy's attack</param>
void Game::counterAttack(Attack t_enemyAttack)
{
	if (checkForWeapon(ItemType::Counter))
	{
		if (t_enemyAttack == Attack::Melee)
		{
			int damageDone = m_player->attack(Attack::Defence) + (*m_playerGear.m_Equiped)->damage();
			m_enemy->damage(damageDone);
			std::cout << "You countered the enemy! You did " << damageDone << " damage." << std::endl;
		}
		else if (t_enemyAttack == Attack::Magic)
		{
			system("cls");
			std::cout << "Enemy broke through your defence!" << std::endl;

			int damageDone = m_enemy->attack(t_enemyAttack);

			if (checkForWeapon(ItemType::Shield))
			{
				damageDone -= (*m_playerGear.m_Equiped)->damage();
				std::cout << "Attack successfully blocked! You soften the blow." << std::endl;
			}
			else
			{
				std::cout << "Selected item is not a shield" << std::endl;
			}

			m_player->damage(damageDone);
			std::cout << "You took " << damageDone << " damage." << std::endl;
		}
		else
		{
			std::cout << "You both miss, no damage done" << std::endl;
		}
	}
	else
	{
		std::cout << "Weapon does not match attack type" << std::endl;
	}
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
	std::cout << "Potions: " << m_playerGear.m_potions << "\t|"; // Output the player's potions

	

	SetConsoleCursorPosition(hConsole, lastCursorPosition); // Set the cursor back to the previous position
}

/// <summary>
/// Displays the shop statistics.
/// <para>Displays the player health and race</para>
/// <para>Displays the player's inventory</para>
/// </summary>
void Game::displayShopStats()
{
	// Display player and enemy statistics
	COORD lastCursorPosition = GetConsoleCursorPosition(hConsole); // Get the current cursor position

	SetConsoleCursorPosition(hConsole, { 60, 0 }); // Set the cursor position
	std::cout << "Player: "; // Output the player and enemy header

	SetConsoleCursorPosition(hConsole, { 60, 1 }); // Set the cursor position
	std::cout << "| Race: " << m_player->getRace(); // Output the player and enemy race

	SetConsoleCursorPosition(hConsole, { 60, 2 }); // Set the cursor position
	std::cout << "| Health: " << m_player->getHealth(); // Output the player and enemy health

	SetConsoleCursorPosition(hConsole, { 60, 3 }); // Set the cursor position
	std::cout << "| Potions: " << m_playerGear.m_potions; // Output the player's potions

	SetConsoleCursorPosition(hConsole, { 60, 4 }); // Set the cursor position
	std::cout << "| Gold: " << m_playerGear.m_gold; // Output the player's potions

	SetConsoleCursorPosition(hConsole, { 60, 5 }); // Set the cursor position
	std::cout << "|------- Inventory -------"; // Output a divider line

	// Display the player inventory
	for (int i = 0; i < m_playerGear.MAX_ITEMS; i++) // Loops through the inventory
	{
		SetConsoleCursorPosition(hConsole, { 60, 6 + static_cast<short>(i) }); // Set the cursor position

		if (m_playerGear.m_inventory[i] == nullptr)
		{
			std::cout << "| - Empty";
		}
		else
		{
			std::cout << "| - " << m_playerGear.m_inventory[i]->name();
		}
	}

	SetConsoleCursorPosition(hConsole, lastCursorPosition); // Set the cursor back to the previous position
}

/// <summary>
/// Updates the game.
/// <para>Checks if the player has died, ends the game if they have.</para>
/// <para>Checks if the enemy has died, spawns new one if they have</para>
/// </summary>
void Game::update()
{
	if (m_player->getHealth() <= 0) // Checks if the player died
	{
		system("cls");
		std::cout << "You died! You survived " << m_roundNumber - 1 << " rounds.\nWho will take the kingdom for your people now?..." << std::endl;
		m_gamePlaying = false;
		system("pause");
	}

	if (m_enemy->getHealth() <= 0) // checks if the enemy died
	{
		system("cls");
		std::cout << "You have slain the enemy!" << std::endl;

		// Give the player some money
		int moneyEarned = rand() % 21 + 10;
		std::cout << "You earned " << moneyEarned << " gold!" << std::endl;
		m_playerGear.m_gold += moneyEarned;

		// Restore player health
		m_player->restoreHealth();
		std::cout << "Your health has been restored" << std::endl;

		system("pause");
		m_enemy->setStats(); // Reset the enemy

		system("cls");
		while (!getInput("Do you want to visit the shop, or keep fighting?\n1 = Visit Shop\n2 = Enter the next battle!\n", 2));

		if (m_input == 1)
		{
			shop();
		}

		system("cls");
		m_roundNumber++;
		std::cout << "Get ready, people! Round " << m_roundNumber << " is about to start!" << std::endl;
		system("pause");
	}
}

/// <summary>
/// Shop screen.
/// </summary>
void Game::shop()
{
	system("cls");

	bool continueShopping = true;

	while (continueShopping)
	{
		system("cls");
		displayShopStats();
		std::cout << "Shop screen." << std::endl << "What do you want to buy:" << std::endl;

		// Take player input and display the shop menu
		if (getInput(m_shopText, NO_OF_ITEMS + 2)) // If the player enters a valid input
		{
			if (m_input == 1)
			{
				if (hasNoWeapons())
				{
					std::cout << "You must have at least 1 weapon in your inventory before starting battle." << std::endl;
				}
				else
				{
					continueShopping = false;
					std::cout << "Come again when you want more goods!" << std::endl;
				}
			}
			else if (m_input < 16)
			{
				// Work out the item price based on its damage and check if the player has enough gold for it
				if (m_playerGear.m_gold >= (ITEM_DAMAGES[m_input - 2] * 10))
				{
					bool spaceInInventory = false;

					// Checks if the player has room in their inventory for the new item
					for (int i = 0; i < m_playerGear.MAX_ITEMS; i++) // Loops through the inventory
					{
						if (m_playerGear.m_inventory[i] == nullptr) // Checks if the inventory slot is empty
						{
							m_playerGear.m_gold -= ITEM_DAMAGES[m_input - 2] * 10; // Minuses the item price from the player's gold
							m_playerGear.m_inventory[i] = new Item{ m_input - 2 }; // Adds the item to the player's inventory
							std::cout << ITEM_NAMES[m_input - 2] << " added to inventory." << std::endl;
							spaceInInventory = true;
							break;
						}
					}

					if (!spaceInInventory) // Checks if the player had no remaining inventory slots
					{
						std::cout << "No room in inventory for the item." << std::endl;
					}
				}
				else
				{
					std::cout << "Not enough money for that item." << std::endl;
				}
			}
			else
			{
				if (m_playerGear.m_gold >= 15)
				{
					std::cout << "Potion added to inventory." << std::endl;
					m_playerGear.m_potions++;
					m_playerGear.m_gold -= 15;
				}
				else
				{
					std::cout << "Not enough gold for a potion." << std::endl;
				}
			}
		}

		system("pause");
	}
}

bool Game::checkForWeapon(ItemType t_attackType)
{
	// Output the attack type
	switch (t_attackType)
	{
	case ItemType::Melee:
		std::cout << "Attack type is Melee";
		break;
	case ItemType::Counter:
		std::cout << "Attack type is Counter";
		break;
	case ItemType::Spell:
		std::cout << "Attack type is Spell";
		break;
	case ItemType::Shield:
		std::cout << "Enemy attacked";
		break;
	}
	
	// Display the inventory
	std::cout << std::endl << "Choose an item to use:" << std::endl;

	// Display the player inventory
	for (int i = 0; i < m_playerGear.MAX_ITEMS; i++) // Loops through the inventory
	{
		if (m_playerGear.m_inventory[i] == nullptr)
		{
			std::cout << "| " << i + 1 << " - Empty" << std::endl;
		}
		else
		{
			std::cout << "| " << i + 1 << " - " << m_playerGear.m_inventory[i]->name() << " - Attack type: ";

			switch (m_playerGear.m_inventory[i]->itemType())
			{
			case ItemType::Melee:
				std::cout << "Melee";
				break;
			case ItemType::Counter:
				std::cout << "Counter";
				break;
			case ItemType::Spell:
				std::cout << "Spell";
				break;
			case ItemType::Shield:
				std::cout << "Shield";
				break;
			}

			std::cout << " - Damage: " << m_playerGear.m_inventory[i]->damage() << std::endl;
		}
	}

	while (!getInput("", 10)); // Loop until a valid input is taken
	
	if (m_playerGear.m_inventory[m_input - 1] == nullptr) // if the player selected an empty slot, return false
	{
		return false;
	}
	else if (m_playerGear.m_inventory[m_input - 1]->itemType() == t_attackType) // if the player selected a matching item, return true
	{
		m_playerGear.m_Equiped = &m_playerGear.m_inventory[m_input - 1];
		return true;
	}

	return false; // if the player selected the wrong type of item, return false
}

/// <summary>
/// Returns true if the inventory is empty of weapons
/// </summary>
/// <returns></returns>
bool Game::hasNoWeapons()
{
	for (int i = 0; i < m_playerGear.MAX_ITEMS; i++) // loop through inventory
	{
		if (m_playerGear.m_inventory[i] != nullptr && m_playerGear.m_inventory[i]->itemType() != ItemType::Shield) // Check if there is a weapon in this inventory slot
		{
			return false; // return false, there is at least one weapon in the inventory
		}
	}

	return true; // Return true if no weapons in the inventory
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