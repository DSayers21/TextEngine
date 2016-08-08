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

void Player::SavePlayer(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("PlrName", m_PlyrName);
	Tree.put("PlrLevel", m_Level);
	Tree.put("PlrGold", m_Gold);

	//If there is create the options tree
	boost::property_tree::ptree Items;
	//Add Items to Tree
	m_SandL.SaveItemsToTree(&Items, m_PlyrItems);

	//Add all the options to the current node
	Tree.add_child("Items", Items);

	//Save the tree to a readable format
	m_IOMan.SaveFile(FilePath, Tree);
}

void Player::LoadPlayer(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_PlyrName = Tree.get<std::string>("PlrName");
	m_Level = Tree.get<unsigned int>("PlrLevel");
	m_Gold = Tree.get<float>("PlrGold");

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_PlyrItems, Items);
}

void Player::AddItem(Item addItem)
{
	m_PlyrItems.push_back(addItem);
}

void Player::RemoveItem(Item remItem)
{
	for (int i = 0; i < m_PlyrItems.size(); i++)
	{
		if (m_Input.CompareStrings(m_PlyrItems[i].GetItemName(), remItem.GetItemName()))
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
		if (Input.CompareStrings(it.GetItemName(), ItemName))
		{
			it;
		}	
	}
	Item* BlankReturn = new Item();
	return BlankReturn;
}