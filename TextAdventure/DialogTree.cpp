#include "DialogTree.h"

DialogOption::DialogOption(std::string Text, int ReturnCode, DialogNode *nxtNode)
{
	_Text = Text;
	_ReturnCode = ReturnCode;
	_nxtNode = nxtNode;
}

DialogNode::DialogNode(std::string Text)
{
	_Text = Text;
}

DialogTree::DialogTree(TxtEgn::COutput& Output)
{
	_Output = &Output;
}


DialogTree::~DialogTree()
{
	for (int i = 0; i < _DialogNodes.size(); i++)
	{
		delete _DialogNodes[i];
	}
	_DialogNodes.clear();
}

void DialogTree::Init()
{
	DialogNode *node0 = new DialogNode("<C8> Hello Brave Warrier");
	DialogNode *node1 = new DialogNode("<C8> I don't want to talk to you");
	DialogNode *node2 = new DialogNode("<C8> I have a quest for you");
	DialogNode *node3 = new DialogNode("<C8> You will get 5 gold you greedy swine!");
	DialogNode *node4 = new DialogNode("<C8> Collect 10 Dandelions");

	node0->_DialogOptions.emplace_back("<C14> Sub Noob", 0, node1);
	node0->_DialogOptions.emplace_back("<C14> Hello Strange Voice", 0, node2);
	_DialogNodes.push_back(node0);

	node1->_DialogOptions.emplace_back("<C14> Aww", 0, nullptr);
	_DialogNodes.push_back(node1);

	node2->_DialogOptions.emplace_back("<C14> K bye", 0, nullptr);
	node2->_DialogOptions.emplace_back("<C14> What is it?", 0, node4);
	node2->_DialogOptions.emplace_back("<C14> What's the pay?", 0, node3);
	_DialogNodes.push_back(node2);

	node3->_DialogOptions.emplace_back("<C14> Okay what is it?", 0, node4);
	node3->_DialogOptions.emplace_back("<C14> That sucks im out!", 0, nullptr);
	_DialogNodes.push_back(node3);

	node4->_DialogOptions.emplace_back("<C14> Let's do it!", 1, nullptr);
	node4->_DialogOptions.emplace_back("<C14> No Way", 0, nullptr);
	_DialogNodes.push_back(node4);
}

int DialogTree::PerformDialog()
{
	if (_DialogNodes.empty())
		return -1;
	DialogNode *CurrentNode = _DialogNodes[0];
	bool isConvo = true;
	while (isConvo)
	{
		//Start Convo
		_Output->WriteSlow(CurrentNode->_Text, true);
		for (int i = 0; i < CurrentNode->_DialogOptions.size(); i++)
		{
			std::string Out = "" + (i + 1) + CurrentNode->_DialogOptions[i]._Text;
			_Output->WriteSlow(Out, true);
		}
		int input;
		std::cin >> input;

		if ((input < 0) || (input > CurrentNode->_DialogOptions.size()))
		{
			_Output->WriteSlow("<C12 Invalid Input!", true);
		}
		else
		{
			//Check for end of convo
			if (CurrentNode->_DialogOptions[input - 1]._nxtNode == nullptr)
			{
				return CurrentNode->_DialogOptions[input - 1]._ReturnCode;
			}
			CurrentNode = CurrentNode->_DialogOptions[input - 1]._nxtNode;
		}
	}
}