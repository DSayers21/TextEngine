#include "Location.h"


Location::Location()
{

}
Location::Location(std::string Name, std::string Desc) : m_Name(Name), m_Desc(Desc)
{
}


Location::~Location()
{
}

std::string Location::BuildPath()
{
	return "Location/" + m_Name;
}

std::string m_Name;
std::string m_Desc;

std::map<std::string, Location*> m_Exits = std::map<std::string, Location*>();

std::vector<Item> m_Items;
std::vector<Object> m_Objects;
std::vector<NPC> m_NPC;

void Location::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_Name = Tree.get<std::string>("LocName");
	m_Desc = Tree.get<std::string>("LocDesc");

	/////////////////Items////////////////////////////////////
	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_Items, Items);

	/////////////////Objects///////////////////////////////////
	//Get Objects child
	boost::property_tree::ptree Objects = Tree.get_child("Objects");
	//Save Objects from Tree into Vector
	m_SandL.SaveObjectsToVector(&m_Objects, Items);

	/////////////////NPCs//////////////////////////////////////
	//Get NPCs child
	boost::property_tree::ptree NPCs = Tree.get_child("NPCs");
	//Save NPCs from Tree into Vector
	m_SandL.SaveNPCsToVector(&m_NPC, Items);

	/////////////////Locations////////////////////////////////
	//Get Locations child
	boost::property_tree::ptree Locations = Tree.get_child("Locations");
	//Save Locations from Tree into Vector
	m_SandL.SaveLocationToMap(&Locations, &m_Exits);
}

void Location::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("LocName", m_Name);
	Tree.put("LocDesc", m_Desc);

	//Items////////////////////////////////////////////////
	boost::property_tree::ptree Items;
	m_SandL.SaveItemsToTree(&Items, m_Items);
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	//Objects//////////////////////////////////////////////
	boost::property_tree::ptree Objects;
	m_SandL.SaveObjectsToTree(&Objects, m_Objects);
	//Add all the options to the current node
	Tree.add_child("Objects", Objects);

	//NPCs/////////////////////////////////////////////////
	boost::property_tree::ptree NPCs;
	m_SandL.SaveNPCsToTree(&NPCs, m_NPC);
	//Add all the options to the current node
	Tree.add_child("NPCs", NPCs);

	//Exits/////////////////////////////////////////////////
	boost::property_tree::ptree Exits;
	m_SandL.SaveLocationToTree(&Exits, m_Exits);
	//Add all the options to the current node
	Tree.add_child("Locations", Exits);

	//Save the tree to a readable format
	m_IOMan.SaveFile(FilePath, Tree);

}