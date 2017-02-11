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

Enemies* Location::FindEnemy(std::string EnemyName)
{
	Enemies* Temp = nullptr;
	int Size = static_cast<int>(m_Enemies.size());
	for (int i = 0; i < Size; i++)
	{
		if (m_Input.CompareStrings(m_Enemies[i].getName(), EnemyName))
			return &m_Enemies[i];
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
	//Load Name And Desc for location
	m_Name = Tree.get<std::string>("LocName");
	m_Desc = Tree.get<std::string>("LocDesc");
	//Load Image
	m_LocationImage = Tree.get<std::string>("LocImage");
	/////////////////Items////////////////////////////////////
	LoadType(Tree, m_Items, "Item", "Items");
	/////////////////Enemy////////////////////////////////////
	LoadType(Tree, m_Enemies, "Enemy", "Enemies");
	/////////////////Weapons////////////////////////////////////
	LoadType(Tree, m_Weapons, "Weapon", "Weapons");
	/////////////////Objects///////////////////////////////////
	//Get Objects child
	LoadType(Tree, m_Objects, "Object", "Objects");
	/////////////////NPCs//////////////////////////////////////
	LoadType(Tree, m_NPC, "NPC", "NPCs");
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
	SaveType(Tree, m_Items, FilePath, "Item", "Items");
	//Enemys////////////////////////////////////////////////
	SaveType(Tree, m_Enemies, FilePath, "Enemy", "Enemies");
	//Weapons////////////////////////////////////////////////
	SaveType(Tree, m_Weapons, FilePath, "Weapon", "Weapons");
	//Objects//////////////////////////////////////////////
	SaveTypeP(Tree, m_Objects, FilePath, "Object", "Objects");
	//NPCs/////////////////////////////////////////////////
	SaveTypeP(Tree, m_NPC, FilePath, "NPC", "NPCs");
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

void Location::AddWeapon(Weapon Wpn)
{
	m_Weapons.push_back(Wpn);
}

void Location::AddObject(Object *Obj)
{
	m_Objects.push_back(Obj);
}

void Location::AddNPC(NPC *npc)
{
	m_NPC.push_back(npc);
}

void Location::AddEnemy(Enemies Enmy)
{
	m_Enemies.push_back(Enmy);
}

void Location::RemEnemy()
{
	m_Enemies.pop_back();
}

void Location::DisplayAll(TxtEgn::COutput* Output)
{
	Output->GetConsole()->Update();

	Output->WriteLine(7, '-');

	std::string Disp = "";
	Disp = "<C7>You are in " + m_Name + ". You see a " + m_Desc + " ";
	
	Disp += DisplayNPCs(Output);
	Disp += DisplayItems(Output);
	Disp += DisplayWeapons(Output);
	Disp += DisplayObjects(Output);
	Disp += DisplayExits(Output);

	Output->WriteSlow(Disp, false);
	Output->GetConsole()->EndLine();

	Output->WriteLine(7, '-');
}

std::string Location::DisplayExits(TxtEgn::COutput* Output)
{
	std::string Return = "";
	for (std::map<std::string, Location*>::iterator ii = m_Exits.begin(); ii != m_Exits.end(); ++ii)
		Return = Return + "<C7>You can travel " + (*ii).first + " to go to " + (*ii).second->GetName() + ". ";
	return Return;
}

std::string Location::DisplayItems(TxtEgn::COutput* Output)
{
	std::string Return = "";
	int Count = 0;
	int Size = static_cast<int>(m_Items.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (i == 0)
				Return = Return + "<C7>You see " + m_Items[i].GetItemName() + ". ";
			else
				Return = Return + "<C7>You then see " + m_Items[i].GetItemName() + ". ";
		}
	}
	return Return;
}

std::string Location::DisplayWeapons(TxtEgn::COutput* Output)
{
	std::string Return = "";
	int Count = 0;
	int Size = static_cast<int>(m_Weapons.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (i == 0)
				Return = Return + "<C7>You see " + m_Weapons[i].GetItemName() + ". ";
			else
				Return = Return + "<C7>You then see " + m_Weapons[i].GetItemName() + ". ";
		}
	}
	return Return;
}

std::string Location::DisplayObjects(TxtEgn::COutput* Output)
{
	std::string Return = "";
	int Count = 0;
	int Size = static_cast<int>(m_Objects.size());

	for (int i = 0; i < Size; i++)
	{
		if (i == 0)
			Return = Return + "<C7>You see " + m_Objects[i]->GetName() + ". ";
		else
			Return = Return + "<C7>You then see " + m_Objects[i]->GetName() + ". ";
	}
	return Return;
}

std::string Location::DisplayNPCs(TxtEgn::COutput* Output)
{
	std::string Return = "";
	int Count = 0;
	int Size = static_cast<int>(m_NPC.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
			Return = Return + "<C7>You see a " + m_NPC[i]->GetGender() + 
			" you overhear that their name is " + m_NPC[i]->GetName() + ". ";
	}
	return Return;
}

std::string Location::DisplayEnemies(TxtEgn::COutput * Output)
{
	std::string Return = "";
	int Count = 0;
	int Size = static_cast<int>(m_Enemies.size());
	if (Size != 0)
	{
		for (int i = 0; i < Size; i++)
			Return = Return + "<C7>You see a creature, It appears to be a " + m_Enemies[i].getName() + ". ";
	}
	return Return;
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

bool Location::InspectAll(TxtEgn::COutput* Output, std::string Compare)
{
	if (InspectItems(Output, Compare))
		return true;
	if (InspectObjects(Output, Compare))
		return true;
	if (InspectNPCs(Output, Compare))
		return true;
	return false;
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

bool Location::InspectWeapons(TxtEgn::COutput * Output, std::string Compare)
{
	int Size = static_cast<int>(m_Weapons.size());
	if (m_Weapons.size() != 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (m_Input.CompareStrings(m_Weapons[i].GetItemName(), Compare))
			{
				Output->WriteSlow("<C7>You see " + m_Weapons[i].GetItemName() + ", it appears to be " + m_Weapons[i].GetItemDesc(), true);
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