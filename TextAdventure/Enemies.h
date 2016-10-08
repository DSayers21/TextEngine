#pragma once
#ifndef EN_H
#define EN_H
#include "Items.h"
#include "Attack.h"
#include "StatBlock.h"
#include <string>
#include <iostream>
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

	Drops loot;
public:
	Enemies(std::string, int, double, double, double, double, double, double, int, int, Item, int);
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
};
#endif
