#include "DialogTree.h"
#include "Item.h"

DialogOption::DialogOption(std::string Text, std::string NxtNode, int ReturnCode, DialogNode *nxtNode)
{
	m_Text = Text;
	m_SNxtNode = NxtNode;
	m_ReturnCode = ReturnCode;
	m_nxtNode = nxtNode;
}

DialogNode::DialogNode(std::string Text)
{
	m_Text = Text;
}

DialogTree::DialogTree()
{

}

DialogTree::~DialogTree()
{
	for (int i = 0; i < m_DialogNodes.size(); i++)
	{
		delete m_DialogNodes[i];
	}
	m_DialogNodes.clear();
}

void DialogTree::Init(std::string FilePath)
{
	Load(FilePath);
}

int DialogTree::PerformDialog(NPC* Person, TxtEgn::COutput* Output, Player* Plr, std::vector<std::string> GoodByeMes)
{
	if (m_DialogNodes.empty())
		return -1;
	DialogNode *CurrentNode = m_DialogNodes[0];
	bool isConvo = true;
	int LastCode = 0;

	while (isConvo)
	{
		//Start Convo
		Output->DisplayColumnsConvo(Person->GetName(), CurrentNode->m_Text, 159, 249, TxtEgn::ALIGN::LEFT);

		//Set Colours for options
		Output->GetConsole()->SetColour(7);
		for (int i = 0; i < CurrentNode->m_DialogOptions.size(); i++)
		{
			switch (CurrentNode->m_DialogOptions[i].m_ReturnCode)
			{
			case 0:
				if (CurrentNode->m_DialogOptions[i].m_nxtNode->m_DialogOptions.size() == 0)
					Output->GetConsole()->SetColour(12);
				else
					Output->GetConsole()->SetColour(7);
				break;
			case 1:
				Output->GetConsole()->SetColour(11);
				break;
			case 2:
				Output->GetConsole()->SetColour(14);
				break;
			}

			Output->WriteSlow("[" + std::to_string(i) + "]\t\t" + CurrentNode->m_DialogOptions[i].m_Text, true);
		}
		
		//Give Items
		CurrentNode->GiveItems(Plr, Output);

		//Check if end
		if (CurrentNode->m_DialogOptions.size() == 0)
			return LastCode;

		//Get input
		std::string Input = m_Input.ParseIntoSentence(Output->GetInput("What say you?"), 0);
		int input = (m_Input.is_number(Input)) ? std::stoi(Input) 
			: m_Input.FindStringPosition(CurrentNode->MakeOptionVector(), Input);

		//Check Goodbye
		if (!m_Input.is_number(Input))
		{
			if (m_Input.FindString(GoodByeMes, Input))
			{
				Output->DisplayColumnsConvo(Person->GetName(), Person->GetGoodBye(), 159, 249, TxtEgn::ALIGN::LEFT);
				isConvo = false;
				return LastCode;
			}
		}

		if ((input < 0) || (input > CurrentNode->m_DialogOptions.size()-1))
			Output->WriteSlow("<C12> Invalid Input!", true);
		else
		{
			//Get Return Code
			LastCode = CurrentNode->m_DialogOptions[input].m_ReturnCode;

			//Go to next node
			CurrentNode = CurrentNode->m_DialogOptions[input].m_nxtNode;
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

void DialogTree::Load(std::string FilePath)
{
	//Temp Vector Used for linking pointers
	std::vector<std::string> _DialogName;
	//Load Data into Tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_DiaName = Tree.get<std::string>("ConversationName");

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

		m_DialogNodes.emplace_back(node);
	}


	//Add dialog options to nodes being held in _DialogNodes vector
	for (int i = 0; i < m_DialogNodes.size(); i++)
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
			int Position = m_Input.FindStringPosition(_DialogName, NextNode);

			//std::cout << i << " |:| " << Position << std::endl;
			//Add option to the _DialogNodes node 
			if (Position != -1)
				m_DialogNodes[i]->m_DialogOptions.emplace_back(Name, NextNode, ReturnCode, m_DialogNodes[Position]);
			else
				m_DialogNodes[i]->m_DialogOptions.emplace_back(Name, NextNode, ReturnCode, nullptr);
		}
		//Get Items child
		boost::property_tree::ptree Items = NodeNum.get_child("Items");
		//Save Items from Tree into Vector
		m_SandL.SaveTreeToVector(m_DialogNodes[i]->m_DialogItems, Items, "Item");
	}
}

void DialogTree::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	boost::property_tree::ptree Nodes;
	//Add the Conversation name to the top of the tree
	Tree.put("ConversationName", m_DiaName);
	//Loop through all the Dialog Nodes in the tree
	for (int i = 0; i < m_DialogNodes.size(); i++)
	{
		//For each node get the node num
		std::string Num = "Node" + std::to_string(i);
		//Create the node num tree for the current node
		boost::property_tree::ptree NodeNum;
		//Add the current nodes dialog to the node num tree
		NodeNum.put("Dialog", m_DialogNodes[i]->m_Text);
		//Check if there are any dialog options in this node
		if (m_DialogNodes[i]->m_DialogOptions.size() > 0)
		{
			//If there is create the options tree
			boost::property_tree::ptree Options;
			//Loop through all the options
			for (int j = 0; j < m_DialogNodes[i]->m_DialogOptions.size(); j++)
			{
				//Get the current option
				DialogOption* Current = &m_DialogNodes[i]->m_DialogOptions[j];
				//Get the option number
				std::string OptNum = "Option" + std::to_string(j);
				//Create the tree for the current option num
				boost::property_tree::ptree OpitonNum;
				//Put all the option information into the tree
				OpitonNum.put("Name", Current->m_Text);
				OpitonNum.put("ReturnCode", Current->m_ReturnCode);
				OpitonNum.put("NextNode", Current->m_SNxtNode);
				//Add the current option num into the options tree
				Options.add_child(OptNum, OpitonNum);
			}
			//Add all the options to the current node
			NodeNum.add_child("Options", Options);
		}
		else 
		{
			//If there is create the options tree
			boost::property_tree::ptree Options;
			NodeNum.add_child("Options", Options);
		}
		//If there is create the options tree
		boost::property_tree::ptree Items;
		//Add Items to Tree
		m_SandL.SaveVecToTree(&Items, m_DialogNodes[i]->m_DialogItems, FilePath, "Item");

		for (int x = 0; x < m_DialogNodes[i]->m_DialogItems.size(); x++)
		{
			m_DialogNodes[i]->m_DialogItems[x].Save(FilePath);
		}

		//Add all the options to the current node
		NodeNum.add_child("Items", Items);

		//Add all the nodes to the nodes tree
		Nodes.add_child(Num, NodeNum);
	}
	//Add the nodes tree to the main tree
	Tree.add_child("Nodes", Nodes);
	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

std::string DialogTree::BuildPath(std::string FilePath)
{
	return FilePath + "/Dialog/" + m_Input.RemoveSpaces(m_DiaName);
}