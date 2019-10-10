#include "Item.h"

// Default constructer
Item::Item() :
	m_name{ ITEM_NAMES[0] },
	m_itemType{ ItemType::Spell },
	m_damage{ ITEM_DAMAGES[0] }
{
}

// Overload constructer
Item::Item(int t_itemNo) :
	m_name{ ITEM_NAMES[0] },
	m_itemType{ ItemType::Spell },
	m_damage{ ITEM_DAMAGES[0] }
{
	if (t_itemNo > 0 && t_itemNo < NO_OF_ITEMS)
	{
		m_name = ITEM_NAMES[t_itemNo];
		m_damage = ITEM_DAMAGES[t_itemNo];

		if (t_itemNo < 5)
		{
			m_itemType = ItemType::Spell;
		}
		else if (t_itemNo < 9)
		{
			m_itemType = ItemType::Melee;
		}
		else if (t_itemNo < 12)
		{
			m_itemType = ItemType::Counter;
		}
		else
		{
			m_itemType = ItemType::Shield;
		}
	}
}
