/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// </summary>

#include "Character.h"

/// <summary>
/// Returns the attack damage of an inputted attack type.
/// </summary>
/// <param name="t_attack">Attack type</param>
/// <returns>Attack damage</returns>
int Character::attack(Attack t_attack)
{
	switch (t_attack)
	{
	case Attack::Magic:
		return 1 + m_stats.m_wisdom / 4;
		break;
	case Attack::Melee:
		return 1 + m_stats.m_strength / 4;
		break;
	case Attack::Defence:
		return 1 + m_stats.m_dexterity / 4;
		break;
	}
}

/// <summary>
/// Returns the health of the character.
/// </summary>
/// <returns></returns>
int Character::getHealth()
{
	return m_health;
}

/// <summary>
/// Minuses the inputted value from the character health.
/// <para>Locks the health to a minimum of 0.</para>
/// </summary>
/// <param name="t_damage"></param>
void Character::damage(int t_damage)
{
	m_health -= t_damage;

	if (m_health < 0)
	{
		m_health = 0;
	}
}

/// <summary>
/// Adds a random number between 3 and 8 to the health
/// </summary>
int Character::takePotion()
{
	int previousHealth = m_health; // Store the previous health
	m_health += rand() % 6 + 3; // Assign a random amount of health between 3 and 8
	
	// If the health is greater than the max health, sets it to the max health
	if (m_health > m_stats.m_constitution)
	{
		m_health = m_stats.m_constitution;
	}

	return m_health - previousHealth; // Minus the previous health from the current to get the amount healed
}

// Restores the character's health to full
void Character::restoreHealth()
{
	m_health = m_stats.m_constitution;
}

/// <summary>
/// Prints out the character's stats
/// </summary>
void Character::printStats()
{
	std::cout << "STR: " << m_stats.m_strength << std::endl;
	std::cout << "DEX: " << m_stats.m_dexterity << std::endl;
	std::cout << "CON: " << m_stats.m_constitution << std::endl;
	std::cout << "WIS: " << m_stats.m_wisdom << std::endl;
}
