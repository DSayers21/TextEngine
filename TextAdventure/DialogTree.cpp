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

DialogTree::DialogTree(TxtEgn::COutput& Output, std::string FilePath)
{
	_Output = &Output;
	_FilePath = FilePath;
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
	//Temp Vector Used for linking pointers
	std::vector<std::string> _DialogName;
	//Load Data into Tree
	boost::property_tree::ptree Tree = IOMan.LoadJSON(_FilePath);
	//Tree that gets Nodes from main tree
	boost::property_tree::ptree Nodes = Tree.get_child("Nodes");
	//Tree to get elements of above Nodes tree e.g. Node1 Node2 ect
	boost::property_tree::ptree NodeNum;
	//Load in all of the dialog NOT the options within the dialog this is done later
	for (int i = 0; i < Nodes.size(); i++)
	{
		//Get name
		std::string NodeName = "Node" + std::to_string(i);
		_DialogName.push_back(NodeName);
		//Get node number 
		NodeNum = Nodes.get_child(NodeName);
		//Get dialog e.g. "Hello Traveller"
		std::string Dialog = NodeNum.get<std::string>("Dialog");
		//Create node and add it to _DialogNodes vector
		DialogNode *node = new DialogNode(Dialog);
		_DialogNodes.emplace_back(node);
	}
	//Add dialog options to nodes being held in _DialogNodes vector
	for (int i = 0; i < _DialogNodes.size(); i++)
	{
		//Get Node number child
		std::string NodeName = "Node" + std::to_string(i);
		NodeNum = Nodes.get_child(NodeName);
		//Get options child
		boost::property_tree::ptree Options = NodeNum.get_child("Options");
		//Loop through all options of current Node
		for (int j = 0; j < Options.size(); j++)
		{
			//Get options number child
			std::string OptionName = "Option" + std::to_string(j);
			std::string NodeName = "Node" + std::to_string(i);
			boost::property_tree::ptree OptionNum = Options.get_child(OptionName);
			//Get all information needed from optionNum
			std::string Name = OptionNum.get<std::string>("Name");
			int ReturnCode = OptionNum.get<int>("ReturnCode");
			std::string NextNode = OptionNum.get<std::string>("NextNode");
			//Find which node is to be pointed to
			int Position = _Input.SearchVector(_DialogName, NextNode);

			//std::cout << i << " |:| " << Position << std::endl;
			//Add option to the _DialogNodes node 
			if (Position != -1)
				_DialogNodes[i]->_DialogOptions.emplace_back(Name, ReturnCode, _DialogNodes[Position]);
			else
				_DialogNodes[i]->_DialogOptions.emplace_back(Name, ReturnCode, nullptr);
		}
	}
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
			_Output->WriteSlow(CurrentNode->_DialogOptions[i]._Text, true);
		
		
		int input = stoi(_Input.ParseIntoSentence(_Output->GetInput("What say you?"), 0));

		if ((input < 0) || (input > CurrentNode->_DialogOptions.size()))
			_Output->WriteSlow("<C12 Invalid Input!", true);
		else
		{
			//Check for end of convo
			if (CurrentNode->_DialogOptions[input - 1]._nxtNode == nullptr)
				return CurrentNode->_DialogOptions[input - 1]._ReturnCode;
			
			CurrentNode = CurrentNode->_DialogOptions[input - 1]._nxtNode;
		}
	}
}

std::string DialogTree::Indent(int level) 
{
	std::string s;
	for (int i = 0; i<level; i++) s += "  ";
	return s;
}

void DialogTree::PrintTree(boost::property_tree::ptree &pt, int level) 
{
	if (pt.empty()) {
		std::cerr << "\"" << pt.data() << "\"";
	}
	else 
	{
		if (level) std::cerr << std::endl;
		std::cerr << Indent(level) << "{" << std::endl;
		for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end();) {
			std::cerr << Indent(level + 1) << "\"" << pos->first << "\": ";
			PrintTree(pos->second, level + 1);
			++pos;
			if (pos != pt.end()) {
				std::cerr << ",";
			}
			std::cerr << std::endl;
		}
		std::cerr << Indent(level) << " }";
	}
	return;
}