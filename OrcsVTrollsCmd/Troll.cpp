/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 07/10/2019
/// </summary>

#include "Troll.h"

Troll::Troll()
{
	m_stats.m_strength = rand() % 11 + 10;
	m_stats.m_dexterity = rand() % 7 + 6;
	m_stats.m_constitution = rand() % 11 + 10;
	m_stats.m_wisdom = rand() % 7 + 6;

	m_health = m_stats.m_constitution;
}
