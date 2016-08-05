#include "Player.h"
#include "Item.h"
#include <TextEngine/InputControl.h>


Player::Player(std::string PlyrName, unsigned int Level, float Gold) :
	m_PlyrName(PlyrName),
	m_Level(Level),
	m_Gold(Gold)
{
	//Empty
}


Player::~Player()
{
	//Empty
}

void Player::AddItem(Item* addItem)
{
	m_PlyrItems.push_back(addItem);
}

void Player::RemoveItem(Item* remItem)
{
	for (int i = 0; i < m_PlyrItems.size(); i++)
	{
		if (m_Input.CompareStrings(m_PlyrItems[i]->GetItemName(), remItem->GetItemName()))
		{
			m_PlyrItems.erase(m_PlyrItems.begin() + i);
			break;
		}
	}
}

Item* Player::GetItem(std::string ItemName)
{
	TxtEgn::InputControl Input;
	for (auto it : m_PlyrItems)
	{
		if (Input.CompareStrings(it->GetItemName(), ItemName))
		{
			it;
		}	
	}
	Item* BlankReturn = new Item();
	return BlankReturn;
}