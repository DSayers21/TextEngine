#include "Player.h"
#include "Item.h"
#include "Location.h"
#include <TextEngine/InputControl.h>
#include "Dice.h"

Player::Player()
{

}

Player::Player(std::string PlyrName, unsigned int Level, float Gold) :
	m_PlyrName(PlyrName),
	m_Level(Level),
	m_Gold(Gold)
{

	m_PC_Stats = RollStats();
	//Empty
}

Player::~Player()
{
	//Empty
}

void Player::Save(std::string FilePath)
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
	m_SandL.SaveVecToTree(&Items, m_PlyrItems, FilePath, "Item");

	//Add all the options to the current node
	Tree.add_child("Items", Items);

	Tree.put("StatBlock", m_PC_Stats.BuildPath(FilePath, m_PlyrName));
	m_PC_Stats.Save(FilePath, m_PlyrName);

	Tree.put("ActiveWeapon", m_Equipped.BuildPath(FilePath));
	m_Equipped.Save(FilePath);

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void Player::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(BuildPath(FilePath));

	m_PlyrName = Tree.get<std::string>("PlrName");
	m_Level = Tree.get<unsigned int>("PlrLevel");
	m_Gold = Tree.get<float>("PlrGold");

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveTreeToVector(&m_PlyrItems, Items, "Item");


	std::string StatsPath = Tree.get<std::string>("StatBlock");
	m_PC_Stats.Load(StatsPath);

	std::string WeapPath = Tree.get<std::string>("ActiveWeapon");
	m_Equipped.Load(WeapPath);
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

void Player::RemoveItem(std::string ItemName)
{
	for (int i = 0; i < m_PlyrItems.size(); i++)
	{
		if (m_Input.CompareStrings(m_PlyrItems[i].GetItemName(), ItemName))
		{
			m_PlyrItems.erase(m_PlyrItems.begin() + i);
			break;
		}
	}
}

void Player::DropItem(TxtEgn::COutput* Out, Location* CurrentLocation, std::string ItemName)
{
	int StrLen = static_cast<int>(m_PlyrItems.size());
	for (int i = 0; i < StrLen; i++)
	{
		if (m_Input.CompareStrings(ItemName, m_PlyrItems[i].GetItemName()))
		{
			Out->WriteSlow("<C11>You have dropped " + m_PlyrItems[i].GetItemName() + " to the ground", true);
			CurrentLocation->AddItem(m_PlyrItems[i]);
			m_PlyrItems.erase(m_PlyrItems.begin() + i);
			return;
		}
	}
	Out->WriteSlow("<C12>You do not have that item.", true);
}

Item Player::GetItem(std::string ItemName)
{
	TxtEgn::InputControl Input;
	for (auto it : m_PlyrItems)
	{
		if (Input.CompareStrings(it.GetItemName(), ItemName))
		{
			return it;
		}	
	}
	Item Blank;
	return Blank;
}

std::string Player::BuildPath(std::string FilePath)
{
	return FilePath + "/PlayerData";
}

void Player::Display(TxtEgn::COutput* Out)
{
	int StrLen = static_cast<int>(m_PlyrItems.size());


	Out->WriteLine(7, '-');

	Out->WriteSlow("<C10> [" + m_PlyrName + "] <C7>: Character Information", true);
	Out->WriteSlow("<C7>|- Your Current Level is: <C11>" + std::to_string(m_Level), true);
	Out->WriteSlow("<C7>|- You currently have: <C14>$" + std::to_string(m_Gold), true);

	if (StrLen > 0)
	{
		Out->WriteSlow("<C7>|- Currently in your inventory you have; ", true);

		Out->DisplayColumns3("Item Name:", "Item Description:", "Item Price($):", 208);

		for (int i = 0; i < StrLen; i++)
		{
			Out->DisplayColumns3(m_PlyrItems[i].GetItemName(), m_PlyrItems[i].GetItemDesc(), "$" + std::to_string(m_PlyrItems[i].GetItemValue()), 13);
			Out->GetConsole()->SetCurrentY(Out->GetConsole()->wherey());
			Out->GetConsole()->Update();
		}
	}
	Out->WriteLine(7, '-');
}


void Player::AddEXP(int val)
{
	m_EXP += val;

	int start_lvl = 0;

	for (int i = 2; i < 6; i++)
	{
		if (m_EXP == m_level_threshold[m_threshold_index] && (m_Level > start_lvl && m_Level <= start_lvl + 4))
		{
			m_level_up = true;
			m_PC_Stats.SetProf(i);
			m_threshold_index++;
		}
		start_lvl += 4;
	}
	
}

StatBlock Player::RollStats()
{
	StatBlock Temp(Roll4d6(), Roll4d6(), Roll4d6(), Roll4d6(), Roll4d6(), Roll4d6());
	m_HP = 10 + Temp.GetCONMod();
	m_MaxHP = m_HP;
	return Temp;
}

double Player::Roll4d6()
{
	int total = 0;
	int temp;
	int smallest = 7;
	Dice D6(6);
	for (int i = 0; i < 4; i++)
	{
		temp = D6.Roll();
		total += temp;
		smallest = (temp < smallest) ? temp : smallest;
	}

	total = total - smallest;
	return total;
}

double Player::WeaponAttack(Weapon Equipped, Enemies* target)
{
	if (target->stats.GetCON() > m_PC_Stats.GetSTR())											//If enemy COn is greater than the PC STR, reduce durability of weapon by 1
		Equipped.setDurability(Equipped.getDurability() - 1);

	return (Equipped.getStrength() + m_PC_Stats.GetSTRMod());
}

void Player::UpdateHP(StatBlock a)
{
	if (m_Level == 1)
		m_HP = 10 + a.GetCONMod();
	else
		m_HP = (m_Level * 10) + a.GetCONMod();
}