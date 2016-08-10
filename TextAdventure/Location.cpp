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
	m_SandL.SaveObjectsToVector(&m_Objects, Objects);

	/////////////////NPCs//////////////////////////////////////
	//Get NPCs child
	boost::property_tree::ptree NPCs = Tree.get_child("NPCs");
	//Save NPCs from Tree into Vector
	m_SandL.SaveNPCsToVector(&m_NPC, NPCs);
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
	m_SandL.SaveItemsToTree(&Items, m_Items, FilePath);
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	//Objects//////////////////////////////////////////////
	boost::property_tree::ptree Objects;
	m_SandL.SaveObjectsToTree(&Objects, m_Objects, FilePath);
	//Add all the options to the current node
	Tree.add_child("Objects", Objects);

	//NPCs/////////////////////////////////////////////////
	boost::property_tree::ptree NPCs;
	m_SandL.SaveNPCsToTree(&NPCs, m_NPC, FilePath);
	//Add all the options to the current node
	Tree.add_child("NPCs", NPCs);

	//Exits/////////////////////////////////////////////////
	boost::property_tree::ptree Exits;
	m_SandL.SaveLocationToTree(&Exits, m_Exits, FilePath);
	//Add all the options to the current node
	Tree.add_child("Locations", Exits);

	//Save the tree to a readable format
	m_IOMan.SaveFile(FilePath, Tree);
}

void Location::AddExit(std::string Direction, Location *Loc)
{
	m_Exits.insert(std::pair<std::string, Location*>(Direction, Loc));
}

void Location::DisplayAll()
{
	std::cout << "LocationName: " << m_Name << std::endl;
	std::cout << "LocationDesc: " << m_Desc << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	for (int i = 0; i < m_Items.size(); i++)
	{
		std::cout << "ItemName: " << m_Items[i].GetItemName() << std::endl;
	}
	std::cout << "--------------------------------------" << std::endl;
	for (int i = 0; i < m_Objects.size(); i++)
	{
		std::cout << "ObjectName: " << m_Objects[i]->GetName() << std::endl;
	}

	if (m_Exits.size() != 0)
	{
		for (std::map<std::string, Location*>::iterator ii = m_Exits.begin(); ii != m_Exits.end(); ++ii)
		{
			std::cout << "Direction: " << ii->first << " To Location: " << ii->second->GetName() << std::endl;
		}
	}
}