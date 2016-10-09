#include "Enemies.h"

Enemies::Enemies()
{

}

Enemies::Enemies(std::string val, int hp_val, double s_val, double d_val, double c_val, double i_val, double w_val, double ch_val, int EXP_val, int G_val, Item item_reward, int armour, int dice, int challenge)
{
	stats = StatBlock(s_val, d_val, c_val, i_val, w_val, ch_val);

	name = val;
	loot.EXP = EXP_val;
	loot.Gold = G_val;
	loot.reward = item_reward;
	current_HP = hp_val;
	max_HP = hp_val;
	AC = armour;
	dice_sides = dice;
	Dice Temp(dice_sides);
	m_roll_dmg = Temp;
	CR = challenge;
}

Enemies::~Enemies()
{
}

double Enemies::TakeDamage(int damage)											//the validity of whether this function is necessary is in question
{
	double a;
	std::cout << " " << name << " takes " << damage << " damage!\n";
	a = current_HP - damage;
	current_HP = a;
	return current_HP;
}
double Enemies::getHP()
{
	return current_HP;
}
double Enemies::getMaxHP()
{
	return max_HP;
}
void Enemies::setHP(double a)
{
	current_HP = a;
}
int Enemies::getEXP()
{
	return loot.EXP;
}
int Enemies::getGold()
{
	return loot.Gold;
}

Item Enemies::getLoot()
{
	return loot.reward;
}

std::string Enemies::getLootName()
{
	return loot.reward.GetItemName();
}

int Enemies::getAC()
{
	return AC;
}

void Enemies::setAC(int val)
{
	AC = val;
}

std::string Enemies::getName()
{
	return name;
}

int Enemies::Attack()
{
	return (m_roll_dmg.Roll() + stats.GetSTRMod());
}

void Enemies::Save(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree;
	//Add the Conversation name to the top of the tree
	Tree.put("name", name);
	Tree.put("current_HP", current_HP);
	Tree.put("max_HP", max_HP);
	Tree.put("AC", AC);
	
	Tree.put("LootExp", loot.EXP);
	Tree.put("LootGold", loot.Gold);

	Tree.put("dice_sides", dice_sides);
	Tree.put("CR", CR);
	//Item
	loot.reward.Save(FilePath);
	
	Tree.put("StatBlock", stats.BuildPath(FilePath, name));
	
	stats.Save(FilePath, name);

	//Save the tree to a readable format
	m_IOMan.SaveFile(BuildPath(FilePath), Tree);
}

void Enemies::Load(std::string FilePath)
{
	//Create Main Tree and Nodes tree
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath);

	name = Tree.get<std::string>("name");
	current_HP = Tree.get<int>("current_HP");
	max_HP = Tree.get<int>("max_HP");
	AC = Tree.get<int>("AC");
	
	loot.EXP = Tree.get<int>("LootExp");
	loot.Gold = Tree.get<int>("LootGold");
	
	dice_sides = Tree.get<int>("dice_sides");
	CR = Tree.get<int>("CR");

	std::string ItemPath = Tree.get<std::string>("LootReward");
	loot.reward.Load(ItemPath);
	
	std::string StatsPath = Tree.get<std::string>("StatBlock");
	stats.Load(StatsPath);
}

std::string Enemies::BuildPath(std::string FilePath)
{
	return FilePath + "/Enemy/" + m_Input.RemoveSpaces(name);
}