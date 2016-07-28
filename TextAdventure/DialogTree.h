#pragma once

#include <string>
#include <vector>
#include <TextEngine/COutput.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
#include <boost/property_tree/ptree.hpp>

class DialogOption;
class DialogNode;

class DialogOption
{
public:
	DialogOption(std::string Text, int ReturnCode, DialogNode *nxtNode);

	std::string _Text;
	int _ReturnCode;
	DialogNode *_nxtNode;
};

class DialogNode
{
public:
	DialogNode(std::string Text);

	std::string _Text;
	std::vector<DialogOption> _DialogOptions;
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

	InOutDataManager IOMan;

	TxtEgn::InputControl _Input;
	std::string _FilePath;

	std::vector<DialogNode*> _DialogNodes;
	TxtEgn::COutput* _Output;
};

