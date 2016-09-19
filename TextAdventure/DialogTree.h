#pragma once

#include <string>
#include <vector>
#include <TextEngine/COutput.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"
#include "Item.h"
#include "Player.h"
#include "NPC.h"

class DialogOption;
class DialogNode;

class DialogOption
{
public:
	DialogOption(std::string Text, std::string NxtNode, int ReturnCode, DialogNode *nxtNode);

	std::string m_Text;
	std::string m_SNxtNode;
	int m_ReturnCode;
	DialogNode *m_nxtNode;
};

class DialogNode
{
public:
	void GiveItems(Player* Plr, TxtEgn::COutput* Output)
	{
		for (int i = 0; i < m_DialogItems.size(); i++)
		{
			Output->WriteSlow("<C11>You receive " + m_DialogItems[i].GetItemName(), true);
			Plr->AddItem(m_DialogItems[i]);
			m_DialogItems.erase(m_DialogItems.begin() + i);
		}
	}

	std::vector<std::string> MakeOptionVector()
	{
		std::vector<std::string> Return;
		for (int i = 0; i < m_DialogOptions.size(); i++)
		{
			Return.push_back(m_DialogOptions[i].m_Text);
		}
		return Return;
	}

	DialogNode(std::string Text);

	std::string m_Text;
	std::vector<DialogOption> m_DialogOptions;
	std::vector<Item> m_DialogItems;
};

class DialogTree
{
public:
	DialogTree();
	~DialogTree();

	void Init(std::string FilePath);

	int PerformDialog(NPC* Person, TxtEgn::COutput* Output, Player* Plr, std::vector<std::string> GoodByeMes);

	void Load(std::string FilePath);
	void Save(std::string FilePath);

	std::string BuildPath(std::string FilePath);

private:
	std::string Indent(int level);
	void PrintTree(boost::property_tree::ptree &pt, int level);
	
	InOutDataManager m_IOMan;

	TxtEgn::InputControl m_Input;
	std::string m_DiaName;
	std::vector<DialogNode*> m_DialogNodes;
	SaveLoadControl m_SandL;
};