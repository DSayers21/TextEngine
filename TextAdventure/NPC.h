#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"

#include <string>
#include <map>
#include <vector>

#include "Item.h"

class DialogTree;

class WantedItem
{
public:
	void Init(Item* WItem, Item* GItem, std::string GiveMessage, int Amount)
	{
		m_wanItem = WItem;
		m_giveItem = GItem;
		m_Amount = Amount;
		m_GiveMessage = GiveMessage;
	}

	boost::property_tree::ptree Save(std::string FilePath)
	{

		//Create Main Tree and Nodes tree
		boost::property_tree::ptree Tree;
		//Add the Conversation name to the top of the tree
		Tree.put("WItmGiveMess", m_GiveMessage);
		Tree.put("WItmAmount", m_Amount);
		Tree.put("WItmWan", m_wanItem->BuildPath(FilePath));
		Tree.put("WItmGive", m_giveItem->BuildPath(FilePath));

		//Save the tree to a readable format
		return Tree;
	}

	void Load(boost::property_tree::ptree TreeLoad)
	{
		m_GiveMessage = TreeLoad.get<std::string>("WItmGiveMess");
		m_Amount = TreeLoad.get<int>("WItmAmount");
		std::string ItmLoad = TreeLoad.get<std::string>("WItmWan");
		m_wanItem->Load(ItmLoad);

		ItmLoad = TreeLoad.get<std::string>("WItmGive");
		m_giveItem->Load(ItmLoad);
	}

	Item* m_wanItem;
	Item* m_giveItem;
	int m_Amount;
	std::string m_GiveMessage;
private:
	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

class NPC
{
public:
	NPC();
	NPC(std::string NPCName, std::string NPCDesc, std::string NPCGender, std::string NPCGoodbye, std::string NPCAlreadyGiven);
	~NPC();

	void Save(std::string FilePath);
	void Load(std::string FilePath);

	std::string BuildPath(std::string FilePath);

private:
	std::string m_Name = "BLANK";
	std::string m_Description = "BLANK";
	std::string m_Gender = "BLANK";
	std::string m_Goodbye = "BLANK";
	std::string m_AlrGivenMes = "BLANK";

	std::vector<WantedItem> m_WantedItems;
	std::vector<Item> m_ShopItems;

	DialogTree* m_Dialog = nullptr;


	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

