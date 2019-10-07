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
	void combat();

	// -------------------------- VARIABLES --------------------------
	bool m_gamePlaying;
	int m_input;

	// --------------------------- OBJECTS ---------------------------
	Character *m_player;
	Character *m_enemy;
	Orc m_orc;
	Troll m_troll;
};

#endif // !GAME_H

