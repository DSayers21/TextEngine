#include "Object.h"
#include "Item.h"
#include "Location.h"
#include "GameWorld.h"
#include "Player.h"

Object::Object()
{

}

Object::Object(std::string Name, std::string Desc,
	std::string ActionWord, std::string m_RemovedDesc, std::string m_ActionConnector) :
	m_Name(Name), m_Desc(Desc), m_ActionWord(ActionWord), m_RemovedDesc(m_RemovedDesc), m_ActionConnector(m_ActionConnector)
{
	
}

Object::~Object()
{

}

void Object::AddExit(std::string Direction, std::string Room)
{
	m_NewExits.insert(std::pair<std::string, std::string>(Direction, Room));
}

void Object::AddItem(Item* sItem)
{
	m_NewItems.push_back(sItem);
}
void Object::RemoveItem(std::string ItmName)
{
	for (int i = 0; i < m_NewItems.size(); i++)
	{
		if (m_Input.CompareStrings(m_NewItems[i]->GetItemName(), ItmName))
		{
			m_NewItems.erase(m_NewItems.begin() + i);
			break;
		}
	}
}

void Object::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("ObjName", m_Name);
	Tree.put("ObjDesc", m_Desc);
	Tree.put("ObjActWord", m_ActionWord);
	Tree.put("ObjActCon", m_ActionConnector);
	Tree.put("ObjRemDesc", m_RemovedDesc);
	Tree.put("ObjItmName", m_ActionItemName);
	Tree.put("ObjIfRemoved", m_IfRemoved);

	///Items
	//If there is create the options tree
	boost::property_tree::ptree Items;
	//Add Items to Tree
	m_SandL.SaveVecToTree(&Items, m_NewItems, FilePath, "Item");
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	///Locations/////////////////////////////////////////////////////////
	//If there is create the options tree
	boost::property_tree::ptree Locations;
	//Add Locations to Tree
	int Count = 0;
	for (std::map<std::string, std::string>::iterator ii = m_NewExits.begin(); ii != m_NewExits.end(); ++ii)
	{
		//Get the option number
		std::string LocNum = "Exit" + std::to_string(Count);
		//Create the tree for the current option num
		boost::property_tree::ptree LocationTree;
		//Put all the option information into the tree
		LocationTree.put("LocName", ii->second);
		LocationTree.put("Direction", ii->first);
		//Add the current option num into the options tree
		Locations.add_child(LocNum, LocationTree);
		Count++;
	}
	//Add all the options to the current node
	Tree.add_child("Locations", Locations);
	//////////////////////////////////////////////////////////////////////

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void Object::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_Name = Tree.get<std::string>("ObjName");
	m_Desc = Tree.get<std::string>("ObjDesc");
	m_ActionWord = Tree.get<std::string>("ObjActWord");
	m_ActionConnector = Tree.get<std::string>("ObjActCon");
	m_RemovedDesc = Tree.get<std::string>("ObjRemDesc");
	m_ActionItemName = Tree.get<std::string>("ObjItmName");
	m_IfRemoved = Tree.get<bool>("ObjIfRemoved");

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveTreeToVector(&m_NewItems, Items, "Item");

	////////////////////////////////////////////////////////////////////////////////////////
	//Get Locations child
	boost::property_tree::ptree Locations = Tree.get_child("Locations");
	//Save Items from Tree into Vector

	for (int i = 0; i < Locations.size(); i++)
	{
		//Get options number child
		std::string LocationCur = "Exit" + std::to_string(i);
		boost::property_tree::ptree LocationNum = Locations.get_child(LocationCur);
		//Get all information needed from optionNum
		std::string LocationName = LocationNum.get<std::string>("LocName");
		std::string Direction = LocationNum.get<std::string>("Direction");
		//Add Location
		m_NewExits.insert(std::pair<std::string, std::string>(Direction, LocationName));
	}
	////////////////////////////////////////////////////////////////////////////////////////
}

std::string Object::BuildPath(std::string FilePath)
{
	return FilePath + "/Object/" + m_Input.RemoveSpaces(m_Name);
}

void Object::ObjectCommand(TxtEgn::COutput* Output, GameWorld* Game, std::string Command, Player* MainPlr, Location* Current)
{
	if (m_IfRemoved)
		Output->WriteSlow("<C12>This has already been done", true);
	else
	{
		if (m_Input.CompareStrings(Command, m_ActionWord))
		{
			for(int i = 0; i < m_NewItems.size(); i++)
				Current->AddItem(*m_NewItems[i]);

			for (std::map<std::string, std::string>::iterator ii = m_NewExits.begin(); ii != m_NewExits.end(); ++ii)
			{
				Location* Found = Game->FindLocation((*ii).second);
				Current->AddExit((*ii).first, Found);
			}
				
			m_IfRemoved = true;
			Output->WriteSlow("<C11>" + m_RemovedDesc, true);
		}
		else
			Output->WriteSlow("<C12>This doesn't work", true);
	}
}

void Object::ObjectAction(TxtEgn::COutput* Output, GameWorld* Game, Location* Current)
{
	if (m_IfRemoved)
		Output->WriteSlow("<C12>This has already been done", true);
	else
	{
		for (std::map<std::string, std::string>::iterator ii = m_NewExits.begin(); ii != m_NewExits.end(); ++ii)
		{
			Location* Found = Game->FindLocation((*ii).second);
			Current->AddExit((*ii).first, Found);
		}
		for (int i = 0; i < m_NewItems.size(); i++)
			Current->AddItem(*m_NewItems[i]);

		m_IfRemoved = true;
		Output->WriteSlow("<C11>" + m_RemovedDesc, true);
	}
}