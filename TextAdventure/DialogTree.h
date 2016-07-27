#pragma once

#include <string>
#include <vector>
#include <TextEngine/COutput.h>

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
	DialogTree(TxtEgn::COutput& Output);
	~DialogTree();

	void Init();

	int PerformDialog();
private:
	std::vector<DialogNode*> _DialogNodes;
	TxtEgn::COutput* _Output;
};

