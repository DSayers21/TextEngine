#include "Object.h"
#include "Item.h"
#include "Location.h"

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

	///Items
	//If there is create the options tree
	boost::property_tree::ptree Items;
	//Add Items to Tree
	m_SandL.SaveItemsToTree(&Items, m_NewItems, FilePath);
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	///Locations/////////////////////////////////////////////////////////
	//If there is create the options tree
	//boost::property_tree::ptree Locations;
	//Add Locations to Tree
	//m_SandL.SaveLocationToTree(&Items, m_NewExits, FilePath);
	//Add all the options to the current node
	//Tree.add_child("Locations", Locations);
	//////////////////////////////////////////////////////////////////////

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void Object::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	Tree.put("ObjName", m_Name);
	Tree.put("ObjDesc", m_Desc);
	Tree.put("ObjActWord", m_ActionWord);
	Tree.put("ObjActCon", m_ActionConnector);
	Tree.put("ObjRemDesc", m_RemovedDesc);
	Tree.put("ObjItmName", m_ActionItemName);

	m_Name = Tree.get<std::string>("ObjName");
	m_Desc = Tree.get<std::string>("ObjDesc");
	m_ActionWord = Tree.get<std::string>("ObjActWord");
	m_ActionConnector = Tree.get<std::string>("ObjActCon");
	m_RemovedDesc = Tree.get<std::string>("ObjRemDesc");
	m_ActionItemName = Tree.get<std::string>("ObjItmName");

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_NewItems, Items);

	////////////////////////////////////////////////////////////////////////////////////////
	//Get Locations child
	//boost::property_tree::ptree Locations = Tree.get_child("Locations");
	//Save Items from Tree into Vector
	//m_SandL.SaveLocationToMap(&Locations, &m_NewExits);
	////////////////////////////////////////////////////////////////////////////////////////
}

std::string Object::BuildPath(std::string FilePath)
{
	return FilePath + "/Object/" + m_Input.RemoveSpaces(m_Name);
}