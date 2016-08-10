#include "NPC.h"
#include "DialogTree.h"


NPC::NPC()
{
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
	Tree.put("Dialog", m_Dialog->BuildPath(FilePath));

	//If there is create the options tree
	boost::property_tree::ptree Items;
	//Add Items to Tree
	m_SandL.SaveItemsToTree(&Items, m_ShopItems, FilePath);

	//Add all the options to the current node
	Tree.add_child("Items", Items);

	//Add Wanted Items
	boost::property_tree::ptree WItems;
	for (int i = 0; i < m_WantedItems.size(); i++)
	{
		//Get the current option
		WantedItem* Current = &m_WantedItems[i];
		//Get the option number
		std::string WItmNum = "WItem" + std::to_string(i);
		boost::property_tree::ptree* WItem = &m_WantedItems[i].Save(FilePath);
		WItems.add_child(WItmNum, *WItem);
	}
	Tree.add_child("WItems", WItems);
	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void NPC::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_Name = Tree.get<std::string>("PlrName");
	m_Description = Tree.get<std::string>("PlrLevel");
	m_Gender = Tree.get<std::string>("PlrGold");
	m_Goodbye = Tree.get<std::string>("PlrName");
	m_AlrGivenMes = Tree.get<std::string>("PlrLevel");

	m_Dialog->Load(FilePath);

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_ShopItems, Items);

	//Add Wanted Items
	boost::property_tree::ptree WItems = Tree.get_child("WItems");
	for (int i = 0; i < m_WantedItems.size(); i++)
	{
		//Get the current option
		WantedItem* Current = &m_WantedItems[i];
		//Get the option number
		std::string WItmNum = "WItem" + std::to_string(i);
		boost::property_tree::ptree* WItem = &m_WantedItems[i].Save(FilePath);
		WItems.add_child(WItmNum, *WItem);


		//Get options number child
		std::string ItemName = "WItem" + std::to_string(i);
		boost::property_tree::ptree ItemNum = Items.get_child(ItemName);
		//Get all information needed from optionNum
		std::string WItmWan = ItemNum.get<std::string>("WItmWan");
		std::string WItmGive = ItemNum.get<std::string>("WItmGive");

		std::string WItmGiveMess = ItemNum.get<std::string>("WItmGiveMess");
		int WItmAmount = ItemNum.get<int>("WItmAmount");
		Item WanItem, GiveItem;
		WanItem.Load(WItmWan);
		GiveItem.Load(WItmGive);

		WantedItem WItm;
		WItm.Init(&WanItem, &GiveItem, WItmGiveMess, WItmAmount);

		m_WantedItems.push_back(WItm);
	}
}

std::string NPC::BuildPath(std::string FilePath)
{
	return FilePath + "/NPC/" + m_Input.RemoveSpaces(m_Name);
}