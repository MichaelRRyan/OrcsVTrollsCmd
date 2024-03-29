/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 07/10/2019
/// </summary>

#include "Orc.h"

Orc::Orc()
{
	setStats();
	m_race = "Orc";
}

void Orc::setStats()
{
	m_stats.m_strength = rand() % 7 + 6;
	m_stats.m_dexterity = rand() % 11 + 10;
	m_stats.m_constitution = rand() % 7 + 6;
	m_stats.m_wisdom = rand() % 11 + 10;

	m_health = m_stats.m_constitution;
}
