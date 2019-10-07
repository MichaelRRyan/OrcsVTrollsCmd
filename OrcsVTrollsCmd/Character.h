#ifndef CHARACTER_H
#define CHARACTER_H

/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// </summary>

#include <iostream>

struct Stats
{
	int m_strength; // Used for melee attack damage
	int m_dexterity; // Used for attack order
	int m_constitution; // Used for health value
	int m_wisdom; // Used for magic
};

class Character {
public:
	void flip() { std::cout << "I know how to flip and I will flipping do it" << std::endl; }
	virtual void walk() { std::cout << "just in case they are too young to walk yet" << std::endl; }
	virtual void fly() = 0; //pure virtual function
	void printStats();

protected:
	Stats m_stats;
	int m_health;
};

#endif // !CHARACTER_H

