#include "NPC.h"
#include "DialogTree.h"


NPC::NPC()
{
}

NPC::NPC(std::string NPCName, std::string NPCDesc, std::string NPCGender, std::string NPCGoodbye, std::string NPCAlreadyGiven)
{
	m_Name = NPCName;
	m_Description = NPCDesc;
	m_Gender = NPCGender;
	m_Goodbye = NPCGoodbye;
	m_AlrGivenMes = NPCAlreadyGiven;

	m_Dialog = new DialogTree(*m_Output);
}

NPC::~NPC()
{
}

DialogTree* m_Dialog;

void NPC::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("NpcName", m_Name);
	Tree.put("NpcDesc", m_Description);
	Tree.put("NpcGender", m_Gender);
	Tree.put("NpcBye", m_Goodbye);
	Tree.put("NpcAlrGiv", m_AlrGivenMes);
	if (m_Dialog != nullptr)
	{
		Tree.put("Dialog", m_Dialog->BuildPath(FilePath));
		m_Dialog->Save(FilePath);
	}
	else
		Tree.put("Dialog", "NULL");

	//If there is create the options tree
	boost::property_tree::ptree Items;
	//Add Items to Tree
	m_SandL.SaveItemsToTree(&Items, m_ShopItems, FilePath);

	//Add all the options to the current node
	Tree.add_child("Items", Items);

	for (int i = 0; i < m_ShopItems.size(); i++)
	{
		m_ShopItems[i].Save(FilePath);
	}

	//Add Wanted Items
	boost::property_tree::ptree WItems;
	for (int i = 0; i < m_WantedItems.size(); i++)
	{
		//Get the current option
		WantedItem* Current = &m_WantedItems[i];
		//Get the option number
		std::string WItmNum = "WItem" + std::to_string(i);

		boost::property_tree::ptree WItem = Current->Save(FilePath);

		WItems.add_child(WItmNum, WItem);
	}
	Tree.add_child("WItems", WItems);
	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void NPC::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_Name = Tree.get<std::string>("NpcName");
	m_Description = Tree.get<std::string>("NpcDesc");
	m_Gender = Tree.get<std::string>("NpcGender");
	m_Goodbye = Tree.get<std::string>("NpcBye");
	m_AlrGivenMes = Tree.get<std::string>("NpcAlrGiv");

	std::string GetDia = Tree.get<std::string>("Dialog");
	if (GetDia != "NULL")
	{
		m_Dialog = new DialogTree(*m_Output);
		m_Dialog->Load(GetDia);
	}

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_ShopItems, Items);

	//Add Wanted Items
	boost::property_tree::ptree WItems = Tree.get_child("WItems");
	for (int i = 0; i < WItems.size(); i++)
	{
		//Get the option number
		std::string WItmNum = "WItem" + std::to_string(i);
		boost::property_tree::ptree ItemNum = WItems.get_child(WItmNum);

		WantedItem WItm;
		WItm.Load(ItemNum);

		m_WantedItems.push_back(WItm);
	}
}

std::string NPC::BuildPath(std::string FilePath)
{
	return FilePath + "/NPC/" + m_Input.RemoveSpaces(m_Name);
}