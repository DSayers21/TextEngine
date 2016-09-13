#pragma once

#include <string>
#include <vector>
#include <TextEngine/COutput.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"
#include "Item.h"

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
	DialogNode(std::string Text);

	std::string m_Text;
	std::vector<DialogOption> m_DialogOptions;
	std::vector<Item> m_DialogItems;
};

class DialogTree
{
public:
	DialogTree();
	DialogTree(TxtEgn::COutput& Output);
	~DialogTree();

	void Init(std::string FilePath);

	int PerformDialog();

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
	TxtEgn::COutput* m_Output;
	SaveLoadControl m_SandL;
};