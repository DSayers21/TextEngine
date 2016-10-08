#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(std::string SItmName, std::string SItmDesc, double SItmValue, bool SStackAble, int strength, int durability)
{
	weapon_strength = strength;
	weapon_durability = durability;
	ItmName = SItmName;
	ItmDesc = SItmDesc;
	ItmValue = SItmValue;
	StackAble = SStackAble;
}


Weapon::~Weapon()
{
}

int Weapon::getStrength()
{
	return weapon_strength;
}
void Weapon::setStrength(int val)
{
	weapon_strength = val;
}
int Weapon::getDurability()
{
	return weapon_durability;
}

void Weapon::setDurability(int val)
{
	weapon_durability = val;
}
