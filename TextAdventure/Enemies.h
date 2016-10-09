#pragma once
#ifndef EN_H
#define EN_H
#include "Item.h"
#include "Dice.h"
//#include "Attack.h"
#include "StatBlock.h"
#include <string>
#include <iostream>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
////////////////////////////////////////////////////////////////////
struct Drops
{
	int EXP, Gold;
	Item reward;
};
////////////////////////////////////////////////////////////////////
class Enemies
{
protected:
	std::string name;
	double current_HP, max_HP;
	int AC;
	int dice_sides;
	Dice m_roll_dmg;
	Drops loot;
	int CR;
public:
	Enemies();
	Enemies(std::string, int, double, double, double, double, double, double, int, int, Item, int, int, int);
	~Enemies();
	double TakeDamage(int);
	double getHP();
	double getMaxHP();
	void setHP(double);
	int getEXP();
	int getGold();
	Item getLoot();
	std::string getLootName();
	int getAC();
	void setAC(int val);
	std::string getName();
	StatBlock stats;

	int Attack();

	void Save(std::string FilePath);
	void Load(std::string FilePath);
	std::string BuildPath(std::string FilePath);
private:
	InOutDataManager m_IOMan;
	TxtEgn::InputControl m_Input;
};
#endif
