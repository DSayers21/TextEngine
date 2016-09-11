#include "GameWorld.h"
#include "Location.h"
#include "DialogTree.h"

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
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath + "/Location/Location");

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
		std::string Path = FilePath + "/Location/" + LocName;

		newLocation->Load(Path);
		newLocation->SetLocationNum(LocName);
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
		boost::property_tree::ptree LocationNum;

		LocationNum.put("LocPath", m_Locations[i]->BuildPathLocNum(FilePath));

		//Exits
		boost::property_tree::ptree Exits;
		int Count = 0;

		std::map<std::string, Location*> newMap = m_Locations[i]->GetExits();
		for (std::map<std::string, Location*>::iterator ii = newMap.begin(); ii != newMap.end(); ++ii)
		{
			//For each node get the node num
			std::string ExiNumber = "Exit" + std::to_string(Count);
			boost::property_tree::ptree ExitNum;

			ExitNum.put("Direction", ii->first);
			ExitNum.put("NextLocation", ii->second->GetLocationNum());

			//Add all the nodes to the nodes tree
			Exits.add_child(ExiNumber, ExitNum);
			Count++;
		}

		//Add the nodes tree to the main tree
		LocationNum.add_child("Exits", Exits);

		//Add all the nodes to the nodes tree
		Locations.add_child(LocNum, LocationNum);
		
		//Save
		std::string OutNum = "Location" + std::to_string(i);
		m_Locations[i]->Save(FilePath, OutNum);
	}

	//Add the nodes tree to the main tree
	Tree.add_child("Locations", Locations);

	//Save the tree to a readable format
	m_IOMan.SaveFile(FilePath + "/Location/Location", Tree);
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

void GameWorld::TestBed()
{
	//Locations
	Location CloudForest("Cloud Forest", "a wide variety of trees all with a perculiar type of leaf.. it almost looks like clouds. You stand in a clearning.");
	CloudForest.SetLocationNum("Location0");
	Location CloudCityOutSkirts("Outskirts of Cloud City", "an enourmous city with hundreds of spires which reach high into the atmosphere. The city seems peaceful with a hive of activty.");
	CloudCityOutSkirts.SetLocationNum("Location1");
	Location CloudCity("Cloud City", "a busseling city center full of people all going about their business.");
	CloudCity.SetLocationNum("Location2");
	Location MysteriousTower("Mysterious Tower", "a strange tower, it appears to be emmitting an ominous dark glow across the sky.");
	MysteriousTower.SetLocationNum("Location3");

	//Updates
	m_Locations.push_back(&CloudForest);
	m_Locations.push_back(&CloudCityOutSkirts);
	m_Locations.push_back(&CloudCity);
	m_Locations.push_back(&MysteriousTower);

	//Exits
	CloudForest.AddExit("North", &CloudCityOutSkirts);
	CloudForest.AddExit("West", &MysteriousTower);
	CloudCity.AddExit("South", &CloudCityOutSkirts);
	CloudCityOutSkirts.AddExit("South", &CloudForest);
	MysteriousTower.AddExit("East", &CloudForest);
	//Items
	Item CityPass("City Pass", "a strange card which reads 'Cloud City Pass'", 50, 0);
	CloudForest.AddItem(CityPass);
	Item NigelsWand("Magic Wand", "a wand of basic level power.", 500, 0);
	//Objects
	Object CloudCityGate("Cloud City Gate", "an enourmous looming gate reaching too high to scale.", "Unlock", "The gate slowly opens allowing you entry to the great city.", "with");
	CloudCityGate.AddExit("North", "Cloud City");
	CloudCityGate.SetActionItemName("City Pass");
	
	CloudCityOutSkirts.AddObject(&CloudCityGate);

	//NPCs
	//Nigel
	NPC Nigel("Nigel Samson", "an etherial floating being with the physical appearance of a cloud", "mysterious figure", "Ta Ta for now chum", "I was missing a vial of blottergale!");
	
	MysteriousTower.AddNPC(&Nigel);
}