#ifndef GAME_H
#define GAME_H

/// <summary>
/// @Author Michael Rainsford Ryan is gay
/// @Date 01/10/2019
/// </summary>

#include <iostream>
#include "Character.h"
#include "Orc.h"
#include "Troll.h"

class Game
{
public:
	Game();
	void startGame();
	
protected:
	void gameLoop();
	void getInput();

	// --------------------------- VARIABLES ---------------------------
	bool m_gamePlaying;
	int m_input;

	// --------------------------- OBJECTS ---------------------------
	Orc m_orc;
	Troll m_troll;
};

#endif // !GAME_H

