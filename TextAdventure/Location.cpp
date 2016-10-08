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

Object* Location::FindObject(std::string ObjName)
{
	Object* Temp = nullptr;
	int Size = static_cast<int>(m_Objects.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_Objects[i]->GetName(), ObjName))
			return m_Objects[i];
	}
	return Temp;
}

NPC* Location::FindNPC(std::string NPCName)
{
	NPC* Temp = nullptr;
	int Size = static_cast<int>(m_NPC.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_NPC[i]->GetName(), NPCName))
			return m_NPC[i];
	}
	return Temp;
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

	m_LocationImage = Tree.get<std::string>("LocImage");

	/////////////////Items////////////////////////////////////
	//Get Items child
	boost::property_tree::ptree Items = Tree.get_child("Items");
	//Save Items from Tree into Vector
	m_SandL.SaveItemsToVector(&m_Items, Items);

	/////////////////Enemy////////////////////////////////////
	//Get Items child
	boost::property_tree::ptree Enemy = Tree.get_child("Enemys");
	//Save Items from Tree into Vector
	m_SandL.SaveEnemysToVector(&m_Enemys, Enemy);

	/////////////////Weapons////////////////////////////////////
	//Get Weapons child
	Items = Tree.get_child("Weapons");
	//Save Items from Tree into Vector
	m_SandL.SaveWeaponsToVector(&m_Weapons, Items);

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
	Tree.put("LocImage", m_LocationImage);

	//Items////////////////////////////////////////////////
	boost::property_tree::ptree Items;
	m_SandL.SaveItemsToTree(&Items, m_Items, FilePath);
	//Add all the options to the current node
	Tree.add_child("Items", Items);

	for (int i = 0; i < m_Items.size(); i++)
		m_Items[i].Save(FilePath);

	//Enemys////////////////////////////////////////////////
	boost::property_tree::ptree Enemys;
	m_SandL.SaveEnemysToTree(&Enemys, m_Enemys, FilePath);
	//Add all the options to the current node
	Tree.add_child("Enemys", Enemys);

	for (int i = 0; i < m_Enemys.size(); i++)
		m_Enemys[i].Save(FilePath);

	//Weapons////////////////////////////////////////////////
	boost::property_tree::ptree Weapons;
	
	m_SandL.SaveWeaponsToTree(&Weapons, m_Weapons, FilePath);
	//Add all the options to the current node
	Tree.add_child("Weapons", Weapons);

	for (int i = 0; i < m_Weapons.size(); i++)
		m_Weapons[i].Save(FilePath);

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
	DisplayWeapons(Output);
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

void Location::DisplayWeapons(TxtEgn::COutput* Output)
{
	int Count = 0;
	int Size = static_cast<int>(m_Weapons.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (i == 0)
				Output->WriteSlow("<C7>You see " + m_Weapons[i].GetItemName() + ".", false);
			else
				Output->WriteSlow("<C7>You then see " + m_Weapons[i].GetItemName() + ".", false);
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
	Output->WriteSlow("<C12>There is no item of that name in the area.", true);
}

void Location::InspectAll(TxtEgn::COutput* Output, std::string Compare)
{
	if (InspectItems(Output, Compare))
		return;
	if (InspectObjects(Output, Compare))
		return;
	if (InspectNPCs(Output, Compare))
		return;
	Output->WriteSlow("<C12>Could not find " + Compare + " in the current area", true);
}

bool Location::InspectItems(TxtEgn::COutput* Output, std::string Compare)
{
	int Size = static_cast<int>(m_Items.size());
	if (m_Items.size() != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (m_Input.CompareStrings(m_Items[i].GetItemName(), Compare))
			{
				Output->WriteSlow("<C7>You see " + m_Items[i].GetItemName() + ", it appears to be " + m_Items[i].GetItemDesc(), true);
				return true;
			}
		}
	}
	return false;
}

bool Location::InspectObjects(TxtEgn::COutput* Output, std::string Compare)
{
	int Size = static_cast<int>(m_Objects.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (m_Input.CompareStrings(m_Objects[i]->GetName(), Compare))
			{
				Output->WriteSlow("<C7>You see " + m_Objects[i]->GetName() + ", it appears to be " + m_Objects[i]->GetDesc(), true);
				return true;
			}
		}
	}
	return false;
}

bool Location::InspectNPCs(TxtEgn::COutput* Output, std::string Compare)
{
	int Size = static_cast<int>(m_NPC.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (m_Input.CompareStrings(m_NPC[i]->GetName(), Compare))
			{
				Output->WriteSlow("<C7>" + m_NPC[i]->GetName() + " is " + m_NPC[i]->GetGender() + " with " + m_NPC[i]->GetDesc(), true);
				return true;
			}
		}
	}
	return false;
}

//Command = unlock
//InitialString = the rest eg. door with key
void Location::CommandObject(TxtEgn::COutput* Output, GameWorld* Game, std::string Command, std::string InitialString, Player* Plr)
{
	std::vector<std::string> OBJReturn = GetObjectFrString(InitialString);
	Object* Obj = FindObject(OBJReturn[0]);

	if (Obj != nullptr)
	{
		if (!Obj->IfRemoved())
		{
			std::vector<std::string> Temp = m_Input.ParseIntoWords(OBJReturn[1]);
			if (Temp.size() > 0)
			{
				std::string ObjName = OBJReturn[0];
				std::string Connector = Temp[0];
				std::string ItemName = m_Input.ParseIntoSentence(Temp, 1);

				if (m_Input.CompareStrings(Obj->GetActionWord(), Command))
				{
					if (m_Input.CompareStrings(Obj->GetActionConnector(), Connector))
					{
						if (Plr->GetItem(ItemName).GetItemName() != "EmptyItem")
						{
							//WriteSlow("<C4> " + Command + " " + "<C11> " + ObjName + " " + "<C14> " + Connector + "<C110> " + ItemName, true);
							Obj->ObjectAction(Output, Game, this);
						}
						else
							Output->WriteSlow("<C12>You do not have this item", true);
					}
					else
						Output->WriteSlow("<C12>This is not understood", true);
				}
				else
					Output->WriteSlow("<C12>The action is not understood", true);
			}
			else
			{
				std::string Connector = Obj->GetActionConnector();
				Connector[0] = toupper(Connector[0]);
				std::string Temp = m_Input.ParseIntoSentence(Output->GetInput("<C10> " + Connector + " what?"), 0);

				if (Plr->GetItem(Temp).GetItemName() != "EmptyItem")
					Obj->ObjectAction(Output, Game, this);
				else
					Output->WriteSlow("<C12>You do not have this item", true);
			}
		}
		else
			Output->WriteSlow("<C12>This has already been done", true);
	}
	else
		Output->WriteSlow("<C12>Object doesn't exist", true);
}

std::vector<std::string> Location::GetObjectFrString(std::string InitialString)
{
	std::vector<std::string> Temp = m_Input.ParseIntoWords(InitialString);
	std::string CurTest = "";
	std::string ObjectName;
	int PosEnd = 0;
	int Size = static_cast<int>(Temp.size());

	for (int i = 0; i < Size; i++)
	{
		CurTest = (CurTest.size() == 0) ? CurTest + Temp[i] : CurTest = CurTest + " " + Temp[i];
		if (FindObject(CurTest) != nullptr)
		{
			ObjectName = CurTest;
			PosEnd = (i != Size) ? i + 1 : i;
		}
	}
	return{ ObjectName, m_Input.ParseIntoSentence(Temp, PosEnd) };
}

void Location::GivetoNPC(std::string Command, TxtEgn::COutput* Output, Player* Plr)
{
	std::vector<std::string> Temp = m_Input.ParseIntoWords(Command);
	std::string CurTest = "";
	std::string Best;
	int PosEnd = 0;
	int Size = static_cast<int>(Temp.size());

	for (int i = 0; i < Size; i++)
	{
		CurTest = (CurTest.size() == 0) ? CurTest + Temp[i] : CurTest = CurTest + " " + Temp[i];
		if (InRoomNPC(CurTest) != nullptr)
		{
			Best = CurTest;
			PosEnd = (i != Size) ? i + 1 : i;
		}
	}
	GiveCommand(Best, m_Input.ParseIntoSentence(Temp, PosEnd), Output, Plr);
}

NPC* Location::InRoomNPC(std::string NPCName)
{
	int Size = static_cast<int>(m_NPC.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_NPC[i]->GetName(), NPCName))
			return m_NPC[i];
	}
	return nullptr;
}

void Location::GiveCommand(std::string Command, std::string ItemName, TxtEgn::COutput* Output, Player* Plr)
{
	int Size = static_cast<int>(m_NPC.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_NPC[i]->GetName(), Command))
			m_NPC[i]->StarGiveItem(Output, Plr, ItemName);
	}
}