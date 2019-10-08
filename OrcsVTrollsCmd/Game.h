#ifndef GAME_H
#define GAME_H

/// <summary>
/// @Author Michael Rainsford Ryan is gay
/// @Date 01/10/2019
/// </summary>

#include <iostream>
#include <string>
#include "Character.h"
#include "Orc.h"
#include "Troll.h"

// Set the const here so that <Windows.h> doesn't interfere
const unsigned long CIN_LIMIT = static_cast<unsigned long>(std::numeric_limits<std::streamsize>::max());

#include <Windows.h>

struct Items
{
	int potions;
	int gold;
};

class Game
{
public:
	// ---------------------- PRUBLIC FUNCTIONS ----------------------
	Game();
	void startGame();
	
protected:
	// --------------------- PROTECTED FUNCTIONS ---------------------
	void gameLoop();
	bool getInput(const std::string t_inputMessage, const int t_inputRange);
	void pickRace();
	void combat();
	void displayCombatStats();
	void update();

	COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

	// -------------------------- VARIABLES --------------------------
	bool m_gamePlaying;
	int m_input;

	// --------------------------- OBJECTS ---------------------------
	Character *m_player;
	Character *m_enemy;
	Orc m_orc;
	Troll m_troll;

	Items m_playersItems;

	// For changing font colour 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};

#endif // !GAME_H

