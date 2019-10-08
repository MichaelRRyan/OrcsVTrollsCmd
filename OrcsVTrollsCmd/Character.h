#ifndef CHARACTER_H
#define CHARACTER_H

/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// </summary>

#include <iostream>

enum class Attack
{
	Magic,
	Melee,
	Defence
};

struct Stats
{
	int m_strength; // Used for melee attack damage
	int m_dexterity; // Used for attack order
	int m_constitution; // Used for health value
	int m_wisdom; // Used for magic
};

class Character {
public:
	int attack(Attack t_attack);
	int getHealth();
	void damage(int t_damage);
	int takePotion();
	void printStats();
	inline std::string getRace() { return m_race; }
	virtual void setStats() = 0;

protected:
	Stats m_stats;
	int m_health;
	std::string m_race;
};

#endif // !CHARACTER_H

