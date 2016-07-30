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