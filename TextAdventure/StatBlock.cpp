#include "StatBlock.h"

StatBlock::StatBlock()
{
}

StatBlock::StatBlock(double s_val, double d_val, double c_val, double i_val, double w_val, double ch_val)
{
	STR = s_val;
	DEX = d_val;
	CON = c_val;
	INT = i_val;
	WIS = w_val;
	CHA = ch_val;

	SetSTRMod(CalcModifier(s_val));
	SetDEXMod(CalcModifier(d_val));
	SetCONMod(CalcModifier(c_val));
	SetINTMod(CalcModifier(i_val));
	SetWISMod(CalcModifier(w_val));
	SetCHAMod(CalcModifier(ch_val));

	proficiency = 2;
}

StatBlock::~StatBlock()
{
}

double StatBlock::CalcModifier(double val)
{
	if (val == 1)
		return -5;
	else if (val >= 2 && val <= 3)
		return -4;
	else if (val >= 4 && val <= 5)
		return -3;
	else if (val >= 6 && val <= 7)
		return -2;
	else if (val >= 8 && val <= 9)
		return -1;
	else if (val >= 10 && val <= 11)
		return 0;
	else if (val >= 12 && val <= 13)
		return 1;
	else if (val >= 14 && val <= 15)
		return 2;
	else if (val >= 16 && val <= 17)
		return 3;
	else if (val >= 18 && val <= 19)
		return 4;
	else if (val >= 20 && val <= 21)
		return 5;
	else if (val >= 22 && val <= 23)
		return 6;
	else if (val >= 24 && val <= 25)
		return 7;
	else if (val >= 26 && val <= 27)
		return 8;
	else if (val >= 28 && val <= 29)
		return 9;
	else if (val == 30)
		return 10;
}

void StatBlock::BuffStat(std::string stat_name, double multiplier)
{
	if (stat_name == "STR")
		STR *= multiplier;
	else if (stat_name == "DEX")
		DEX *= multiplier;
	else if (stat_name == "CON")
		CON *= multiplier;
	else if (stat_name == "INT")
		INT *= multiplier;
	else if (stat_name == "WIS")
		WIS *= multiplier;
	else if (stat_name == "CHA")
		CHA *= multiplier;
}

void StatBlock::DeBuffStat(std::string stat_name, double multiplier)
{
	if (stat_name == "STR")
		STR *= multiplier;
	else if (stat_name == "DEX")
		DEX *= multiplier;
	else if (stat_name == "CON")
		CON *= multiplier;
	else if (stat_name == "INT")
		INT *= multiplier;
	else if (stat_name == "WIS")
		WIS *= multiplier;
	else if (stat_name == "CHA")
		CHA *= multiplier;
}

//Save and Load Stat Block
void StatBlock::Save(std::string FilePath, std::string Name)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("STR", STR);
	Tree.put("DEX", DEX);
	Tree.put("CON", CON);
	Tree.put("INT", INT);
	Tree.put("WIS", WIS);
	Tree.put("CHA", CHA);

	Tree.put("STR_mod", STR_mod);
	Tree.put("DEX_mod", DEX_mod);
	Tree.put("CON_mod", CON_mod);
	Tree.put("INT_mod", INT_mod);
	Tree.put("WIS_mod", WIS_mod);
	Tree.put("CHA_mod", CHA_mod);

	Tree.put("proficiency", proficiency);
	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath, Name), Tree);
}

void StatBlock::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	STR = Tree.get<double>("STR");
	DEX = Tree.get<double>("DEX");
	CON = Tree.get<double>("CON");
	INT = Tree.get<double>("INT");
	WIS = Tree.get<double>("WIS");
	CHA = Tree.get<double>("CHA");

	STR_mod = Tree.get<int>("STR_mod");
	DEX_mod = Tree.get<int>("DEX_mod");
	CON_mod = Tree.get<int>("CON_mod");
	INT_mod = Tree.get<int>("INT_mod");
	WIS_mod = Tree.get<int>("WIS_mod");
	CHA_mod = Tree.get<int>("CHA_mod");

	proficiency = Tree.get<int>("proficiency");
}

std::string StatBlock::BuildPath(std::string FilePath, std::string Name)
{
	return FilePath + "/StatBlocks/" + m_Input.RemoveSpaces(Name);
}