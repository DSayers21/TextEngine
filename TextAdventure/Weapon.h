#pragma once
#include "Item.h"
#ifndef WEP_H
#define WEP_H
class Weapon :public Item
{
protected:
	int weapon_strength;
	int weapon_durability;
public:
	Weapon();
	Weapon(std::string SItmName, std::string SItmDesc, double SItmValue, bool SStackAble, int strength, int durability);
	~Weapon();
	int getStrength();
	void setStrength(int val);
	int getDurability();
	void setDurability(int val);
};

#endif
