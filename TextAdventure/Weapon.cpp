#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(std::string SItmName, std::string SItmDesc, double SItmValue, bool SStackAble, int strength, int durability)
{
	weapon_strength = strength;
	weapon_durability = durability;

	m_ItmName = SItmName;
	m_ItmDesc = SItmDesc;
	m_ItmValue = SItmValue;
	m_Stackable = SStackAble;
}

Weapon::~Weapon()
{
}

int Weapon::getStrength()
{
	return weapon_strength;
}
void Weapon::setStrength(int val)
{
	weapon_strength = val;
}
int Weapon::getDurability()
{
	return weapon_durability;
}

void Weapon::setDurability(int val)
{
	weapon_durability = val;
}

void Weapon::Save(std::string FilePath)
{//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("ItmName", m_ItmName);
	Tree.put("ItmDesc", m_ItmDesc);
	Tree.put("ItmValue", m_ItmValue);
	Tree.put("ItmStack", m_Stackable);

	Tree.put("weapon_strength", weapon_strength);
	Tree.put("weapon_durability", weapon_durability);

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void Weapon::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_ItmName = Tree.get<std::string>("ItmName");
	m_ItmDesc = Tree.get<std::string>("ItmDesc");
	m_ItmValue = Tree.get<float>("ItmValue");
	m_Stackable = Tree.get<bool>("ItmStack");

	weapon_strength = Tree.get<int>("weapon_strength");
	weapon_durability = Tree.get<int>("weapon_durability");
}

std::string Weapon::BuildPath(std::string FilePath)
{
	return FilePath + "/Weapon/" + m_Input.RemoveSpaces(m_ItmName);
}