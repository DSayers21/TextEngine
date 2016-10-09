#pragma once
#include "Item.h"
#ifndef WEP_H
#define WEP_H
class Weapon :public Item
{
protected:
	int weapon_strength;
	int weapon_durability;
	int m_dmg_dice;
public:
	Weapon();
	Weapon(std::string SItmName, std::string SItmDesc, double SItmValue, bool SStackAble, int strength, int durability, int dice);
	~Weapon();
	int getStrength();
	void setStrength(int val);
	int getDurability();
	void setDurability(int val);
	int getDmgDice() { return m_dmg_dice; }

	void Save(std::string FilePath);
	void Weapon::Load(std::string FilePath);
	std::string BuildPath(std::string FilePath);
};

#endif