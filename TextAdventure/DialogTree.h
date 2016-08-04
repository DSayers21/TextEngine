#pragma once

#include <string>
#include <vector>
#include <TextEngine/COutput.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
#include <boost/property_tree/ptree.hpp>

class DialogOption;
class DialogNode;
class Item;

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
	DialogTree(TxtEgn::COutput& Output, std::string FilePath);
	~DialogTree();

	void Init();

	int PerformDialog();
private:
	std::string Indent(int level);
	void PrintTree(boost::property_tree::ptree &pt, int level);

	void LoadTree();
	void SaveTree();

	InOutDataManager m_IOMan;

	TxtEgn::InputControl m_Input;
	std::string m_FilePath;

	std::vector<DialogNode*> m_DialogNodes;
	TxtEgn::COutput* m_Output;
};

