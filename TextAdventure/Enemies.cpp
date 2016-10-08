#include "Enemies.h"

Enemies::Enemies(std::string val, int hp_val, double s_val, double d_val, double c_val, double i_val, double w_val, double ch_val, int EXP_val, int G_val, Item item_reward, int armour)
{
	stats = StatBlock(s_val, d_val, c_val, i_val, w_val, ch_val);

	name = val;
	loot.EXP = EXP_val;
	loot.Gold = G_val;
	loot.reward = item_reward;
	current_HP = hp_val;
	max_HP = hp_val;
	AC = armour;
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
	return (4 + stats.GetSTRMod());
}

