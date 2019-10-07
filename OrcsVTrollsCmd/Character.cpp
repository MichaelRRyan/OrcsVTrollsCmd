/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// </summary>

#include "Character.h"

void Character::printStats()
{
	std::cout << "STR: " << m_stats.m_strength << std::endl;
	std::cout << "DEX: " << m_stats.m_dexterity << std::endl;
	std::cout << "CON: " << m_stats.m_constitution << std::endl;
	std::cout << "WIS: " << m_stats.m_wisdom << std::endl;
}
