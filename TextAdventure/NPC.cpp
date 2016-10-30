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

	m_Dialog = new DialogTree();
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
	m_SandL.SaveVecToTree(&Items, m_ShopItems, FilePath, "Item");

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
		m_Dialog = new DialogTree();
		m_Dialog->Load(GetDia);
	}

	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveTreeToVector(m_ShopItems, Items, "Item");

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

void NPC::StartConversation(TxtEgn::COutput* Output, Player* Plr)
{
	int ReturnCode = m_Dialog->PerformDialog(this, Output, Plr, m_GoodByeMes);
	if (ReturnCode == 2)
		StartShop(Output, Plr);
}

void NPC::StartShop(TxtEgn::COutput* Output, Player* Plr)
{
	bool StillShop = true;

	DisplayShop(Output);
	while (StillShop)
	{
		std::string Temp = m_Input.ParseIntoSentence(Output->GetInput("What would you like to buy?"), 0);

		if (m_Input.FindString(m_GoodByeMes, Temp))
			StillShop = false;

		else if ((Temp == "look"))
			DisplayShop(Output);
		else
			PurchaseItem(Output, Plr, Temp);
	}
	Output->DisplayColumnsConvo(m_Name, m_Goodbye, 159, 249, TxtEgn::ALIGN::LEFT);
}

void NPC::DisplayShop(TxtEgn::COutput* Output)
{
	int Size = static_cast<int>(m_ShopItems.size());
	Output->DisplayColumns3("Item Name:", "Item Description:", "Item Price($):", 224, TxtEgn::ALIGN::CENTER);
	for (int i = 0; i < Size; i++)
		Output->DisplayColumns3(m_ShopItems[i].GetItemName(), m_ShopItems[i].GetItemDesc(), "$" + std::to_string(m_ShopItems[i].GetItemValue()), 14, TxtEgn::ALIGN::LEFT);
}

void NPC::PurchaseItem(TxtEgn::COutput* Output, Player* Plr, std::string ItemName)
{
	NPC* ReturnCon = this;
	int Size = static_cast<int>(m_ShopItems.size());
	int Difference;
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_ShopItems[i].GetItemName(), ItemName))
		{
			if (m_ShopItems[i].GetItemValue() <= Plr->GetPlyrGold())
			{
				Plr->SetPlyrGold(Plr->GetPlyrGold() - m_ShopItems[i].GetItemValue());
				Plr->AddItem(m_ShopItems[i]);
				Output->WriteSlow("<C11>You bought " + m_ShopItems[i].GetItemName() + " for" + " <C14>$" + std::to_string(m_ShopItems[i].GetItemValue()), true);
			}
			else
			{
				Difference = m_ShopItems[i].GetItemValue() - Plr->GetPlyrGold();
				Output->WriteSlow("<C12> You don't have enough for that, you need an extra <C14>$" + std::to_string(Difference), true);
			}
		}
	}
}

void NPC::StarGiveItem(TxtEgn::COutput* Output, Player* Plr, std::string ItemName)
{
	bool FoundAny = false;
	for (int i = 0; i < m_WantedItems.size(); i++)
	{
		if (m_Input.CompareStrings(m_WantedItems[i].m_wanItem.GetItemName(), ItemName))
		{
			FoundAny = true;
			if (Plr->GetItem(ItemName).GetItemName() != "EmptyItem")
			{
				if (m_WantedItems[i].m_Amount > 0)
				{
					Output->DisplayColumnsConvo(m_Name, m_WantedItems[i].m_GiveMessage, 159, 249, TxtEgn::ALIGN::LEFT);
					Output->WriteLine(8, '-');
					Output->WriteSlow("<C12> You gave " + m_Name + ", " + Plr->GetItem(ItemName).GetItemName(), true);
					Output->WriteSlow("<C11> You received " + m_WantedItems[i].m_giveItem.GetItemName(), true);
					Plr->RemoveItem(ItemName);
					Plr->AddItem(m_WantedItems[i].m_giveItem);
					m_WantedItems[i].m_Amount = m_WantedItems[i].m_Amount - 1;
					Output->WriteLine(7, '=');
				}
				else
					Output->DisplayColumnsConvo(m_Name, "I dont need that anymore", 159, 249, TxtEgn::ALIGN::LEFT);
			}
			else
			{
				if (m_WantedItems[i].m_Amount > 0)
					Output->DisplayColumnsConvo(m_Name, "I am looking for that, but you dont appear to have it!", 159, 249, TxtEgn::ALIGN::LEFT);
				else
					Output->DisplayColumnsConvo(m_Name, "I dont need that anymore", 159, 249, TxtEgn::ALIGN::LEFT);
			}
		}
	}
	if (!FoundAny)
		Output->DisplayColumnsConvo(m_Name, "What would I want with that!", 159, 249, TxtEgn::ALIGN::LEFT);
}