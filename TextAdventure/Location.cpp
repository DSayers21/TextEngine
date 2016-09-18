#include "Location.h"

Location::Location()
{

}
Location::Location(std::string Name, std::string Desc) : m_Name(Name), m_Desc(Desc)
{
}


Location::~Location()
{
}

std::string Location::BuildPath(std::string FilePath)
{
	return FilePath + "/Location/" + m_Input.RemoveSpaces(m_Name);
}

std::string Location::BuildPathLocNum(std::string FilePath)
{
	return FilePath + "/Location/" + m_Input.RemoveSpaces(m_LocationNum);
}

void Location::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	m_Name = Tree.get<std::string>("LocName");
	m_Desc = Tree.get<std::string>("LocDesc");

	/////////////////Items////////////////////////////////////
	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_Items, Items);

	/////////////////Objects///////////////////////////////////
	//Get Objects child
	boost::property_tree::ptree Objects = Tree.get_child("Objects");

	//Save Objects from Tree into Vector
	m_SandL.SaveObjectsToVector(&m_Objects, Objects);

	/////////////////NPCs//////////////////////////////////////
	//Get NPCs child
	boost::property_tree::ptree NPCs = Tree.get_child("NPCs");
	//Save NPCs from Tree into Vector
	m_NPC = m_SandL.SaveNPCsToVector(m_NPC, NPCs);
}

void Location::Save(std::string FilePath, std::string Num)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("LocName", m_Name);
	Tree.put("LocDesc", m_Desc);

	//Items////////////////////////////////////////////////
	boost::property_tree::ptree Items;
	m_SandL.SaveItemsToTree(&Items, m_Items, FilePath);
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	for (int i = 0; i < m_Items.size(); i++)
		m_Items[i].Save(FilePath);

	//Objects//////////////////////////////////////////////
	boost::property_tree::ptree Objects;
	m_SandL.SaveObjectsToTree(&Objects, m_Objects, FilePath);
	//Add all the options to the current node
	Tree.add_child("Objects", Objects);

	for (int i = 0; i < m_Objects.size(); i++)
		m_Objects[i]->Save(FilePath);

	//NPCs/////////////////////////////////////////////////
	boost::property_tree::ptree NPCs;
	m_SandL.SaveNPCsToTree(&NPCs, m_NPC, FilePath);
	//Add all the options to the current node
	Tree.add_child("NPCs", NPCs);

	for (int i = 0; i < m_NPC.size(); i++)
		m_NPC[i]->Save(FilePath);

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath, Num), Tree);
}
void Location::AddExit(std::string Direction, Location *Loc)
{
	m_Exits.insert(std::pair<std::string, Location*>(Direction, Loc));
}

void Location::AddItem(Item Itm)
{
	m_Items.push_back(Itm);
}

void Location::AddObject(Object *Obj)
{
	m_Objects.push_back(Obj);
}

void Location::AddNPC(NPC *npc)
{
	m_NPC.push_back(npc);
}

void Location::DisplayAll(TxtEgn::COutput* Output)
{
	Output->GetConsole()->Update();

	Output->WriteLine(7, '-');

	Output->WriteSlow("<C7>You are in " + m_Name + ". You see a " + m_Desc, false);
	DisplayNPCs(Output);
	DisplayItems(Output);
	DisplayObjects(Output);
	DisplayExits(Output);

	Output->GetConsole()->EndLine();

	Output->WriteLine(7, '-');
}

void Location::DisplayExits(TxtEgn::COutput* Output)
{
	for (std::map<std::string, Location*>::iterator ii = m_Exits.begin(); ii != m_Exits.end(); ++ii)
		Output->WriteSlow("<C7>You can travel " + (*ii).first + " to go to " + (*ii).second->GetName() + ".", false);
}

void Location::DisplayItems(TxtEgn::COutput* Output)
{
	int Count = 0;
	int Size = static_cast<int>(m_Items.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (i == 0)
				Output->WriteSlow("<C7>You see " + m_Items[i].GetItemName() + ".", false);
			else
				Output->WriteSlow("<C7>You then see " + m_Items[i].GetItemName() + ".", false);
		}
	}
}

void Location::DisplayObjects(TxtEgn::COutput* Output)
{
	int Count = 0;
	int Size = static_cast<int>(m_Objects.size());

	for (int i = 0; i < Size; i++)
	{
		if (i == 0)
			Output->WriteSlow("<C7>You see " + m_Objects[i]->GetName() + ".", false);
		else
			Output->WriteSlow("<C7>You then see " + m_Objects[i]->GetName() + ".", false);
	}
}

void Location::DisplayNPCs(TxtEgn::COutput* Output)
{
	int Count = 0;
	int Size = static_cast<int>(m_NPC.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
			Output->WriteSlow("<C7>You see a " + m_NPC[i]->GetGender() + " you overhear that their name is " + m_NPC[i]->GetName() + ".", false);
	}
}

Location* Location::GoCommand(std::string Direction)
{
	Location* ReturnLoc = this;
	for (std::map<std::string, Location*>::iterator ii = m_Exits.begin(); ii != m_Exits.end(); ++ii)
	{
		if (m_Input.CompareStrings((*ii).first, Direction))
			ReturnLoc = (*ii).second;
	}
	return ReturnLoc;
}

std::string Location::BuildPath(std::string FilePath, std::string LocationNum)
{
	std::string Ret = FilePath + "/Location/" + m_Input.RemoveSpaces(LocationNum);
	std::cout << Ret << std::endl;
	return Ret;
}

void Location::PickUpItem(TxtEgn::COutput* Output, Player* Plr, std::string ItemName)
{
	int Size = static_cast<int>(m_Items.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_Items[i].GetItemName(), ItemName))
		{
			Output->WriteSlow("<C11>You pick up " + m_Items[i].GetItemName(), true);
			Plr->AddItem(m_Items[i]);
			m_Items.erase(m_Items.begin() + i);
			return;
		}
	}
}