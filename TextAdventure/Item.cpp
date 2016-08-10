#include "Item.h"

Item::Item()
{
	//Empty
}

Item::Item(std::string ItmName, std::string ItmDesc, float ItmValue, bool Stackable) :
	m_ItmName(ItmName),
	m_ItmDesc(ItmDesc),
	m_ItmValue(ItmValue),
	m_Stackable(Stackable)

{
	
}

Item::~Item()
{
	//Empty
}

Item::Item(const Item& other)
{
	m_ItmName = other.m_ItmName;
	m_ItmDesc = other.m_ItmDesc;
	m_ItmValue = other.m_ItmValue;
	m_Stackable = other.m_Stackable;
}

Item Item::operator=(const Item& other)
{
	m_ItmName = other.m_ItmName;
	m_ItmDesc = other.m_ItmDesc;
	m_ItmValue = other.m_ItmValue;
	m_Stackable = other.m_Stackable;

	return *this;
}

void Item::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_ItmName = Tree.get<std::string>("ItmName");
	m_ItmDesc = Tree.get<std::string>("ItmDesc");
	m_ItmValue = Tree.get<float>("ItmValue");
	m_Stackable = Tree.get<bool>("ItmStack");
}

void Item::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("ItmName", m_ItmName);
	Tree.put("ItmDesc", m_ItmDesc);
	Tree.put("ItmValue", m_ItmValue);
	Tree.put("ItmStack", m_Stackable);
	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

std::string Item::BuildPath(std::string FilePath)
{
	return FilePath + "/Item/" + m_Input.RemoveSpaces(m_ItmName);
}