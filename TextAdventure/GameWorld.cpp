#include "GameWorld.h"
#include "Location.h"

void PrintTree(boost::property_tree::ptree &pt, int level);
std::string Indent(int level);

void Display(std::vector<Location*>& Locations)
{
	for (int i = 0; i < Locations.size(); i++)
	{
		std::cout << Locations[i]->GetName() << std::endl;
		std::cout << Locations[i]->GetDesc() << std::endl;
	}
}

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::Load(std::string FilePath)
{
	//Temp Vector Used for linking pointers
	std::vector<std::string> _LocationNames;
	//Load Data into Tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath + "/Location");

	m_GameName = Tree.get<std::string>("GameName");;

	//Tree that gets Nodes from main tree
	boost::property_tree::ptree Nodes = Tree.get_child("Locations");
	//Tree to get elements of above Nodes tree e.g. Location0, Location1 ect
	boost::property_tree::ptree LocNum;
	//Load in all of the dialog NOT the options within the dialog this is done later
	for (int i = 0; i < Nodes.size(); i++)
	{
		//Get name
		std::string LocName = "Location" + std::to_string(i);
		_LocationNames.push_back(LocName);
		//Get node number 
		LocNum = Nodes.get_child(LocName);
		//Get Location information
		//Create and Add to vector
		Location* newLocation = new Location();
		std::string Path = FilePath + "/" + LocName;

		newLocation->Load(Path);

		m_Locations.emplace_back(newLocation);
	}

	//Add dialog options to nodes being held in _DialogNodes vector
	for (int i = 0; i < m_Locations.size(); i++)
	{
		//Get Node number child
		std::string LocationName = "Location" + std::to_string(i);
		LocNum = Nodes.get_child(LocationName);
		//Get options child
		boost::property_tree::ptree Exits = LocNum.get_child("Exits");
		//Loop through all options of current Node
		for (int j = 0; j < Exits.size(); j++)
		{
			//Get options number child
			std::string ExitName = "Exit" + std::to_string(j);
			std::string LocName = "Location" + std::to_string(i);
			boost::property_tree::ptree ExitNum = Exits.get_child(ExitName);
			//Get all information needed from optionNum
			std::string Direction = ExitNum.get<std::string>("Direction");
			std::string NextLocation = ExitNum.get<std::string>("NextLocation");

			//Find which node is to be pointed to
			int Position = m_Input.SearchVector(_LocationNames, NextLocation);
			//std::cout << i << " |:| " << Position << std::endl;
			//Add option to the _DialogNodes node 

			if (Position != -1)
				m_Locations[i]->AddExit(Direction, m_Locations[Position]);
		}
	}
	for (int i = 0; i < m_Locations.size(); i++)
	{
		m_Locations[i]->DisplayAll();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	}
}

void GameWorld::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	boost::property_tree::ptree Locations;
	//Add the GameName name to the top of the tree
	Tree.put("GameName", m_GameName);
	//Loop through all the Locations in the tree

	for (int i = 0; i < m_Locations.size(); i++)
	{
		//For each node get the node num
		std::string LocNum = "Location" + std::to_string(i);
		//Create the node num tree for the current node
		boost::property_tree::ptree LocationTree;
		//Add the current nodes dialog to the node num tree

		m_Locations[i]->Save(FilePath);


	}

	//Save the tree to a readable format
	m_IOMan.SaveFile(FilePath + "/Location", Tree);
}

void PrintTree(boost::property_tree::ptree &pt, int level)
{
	if (pt.empty()) {
		std::cerr << "\"" << pt.data() << "\"";
	}
	else
	{
		if (level) std::cerr << std::endl;
		std::cerr << Indent(level) << "{" << std::endl;
		for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end();) {
			std::cerr << Indent(level + 1) << "\"" << pos->first << "\": ";
			PrintTree(pos->second, level + 1);
			++pos;
			if (pos != pt.end()) {
				std::cerr << ",";
			}
			std::cerr << std::endl;
		}
		std::cerr << Indent(level) << " }";
	}
	return;
}

std::string Indent(int level)
{
	std::string s;
	for (int i = 0; i<level; i++) s += "  ";
	return s;
}