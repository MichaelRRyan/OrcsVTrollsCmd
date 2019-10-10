#pragma once

#include <string>

const int NO_OF_ITEMS{ 15 };

const std::string ITEM_NAMES[NO_OF_ITEMS]{
	"Flame", "Fireball", "Firebolt", "Small Explosion", "Magic Nuke",
	"Std Sword", "Rapier", "Broadsword", "Long Sword", "Dagger",
	"Knife", "Short Sword", "Wooden Shield", "Iron Shield", "Steel Shield" };

const int ITEM_DAMAGES[NO_OF_ITEMS]{
	1, 3, 5, 7, 10, // Spells
	2, 4, 6, 10, // Melee
	2, 5, 10, // Counter
	2, 5, 10 }; // Shields

enum class ItemType
{
	Spell,
	Melee,
	Counter,
	Shield
};

class Item
{
public:
	Item();
	Item(int t_itemNo);

	std::string name() { return m_name; }
	ItemType itemType() { return m_itemType; }
	int damage() { return m_damage; }

protected:
	std::string m_name;
	ItemType m_itemType;
	int m_damage;

};

