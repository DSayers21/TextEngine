#pragma once
#include <string>
#include <cstdlib>
#include <vector>
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/COutput.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"
#include "Weapon.h"
#include "Enemies.h"
#include "StatBlock.h"
class Item;
class Location;

class Player
{
public:
	Player();
	Player(std::string PlyrName, unsigned int Level, float Gold);
	~Player();

	void Save(std::string FilePath);
	void Load(std::string FilePath);

	void AddItem(Item addItem);
	void RemoveItem(Item remItem);
	void RemoveItem(std::string ItemName);
	void DropItem(TxtEgn::COutput* Out, Location* CurrentLocation, std::string ItemName);

	void Display(TxtEgn::COutput* Out);
	
	
	
	//Setters
	void SetPlyrName(std::string PlyrName) { m_PlyrName = PlyrName; }
	void SetHP(int val) {m_HP = val; }
	void SetPlyrLevel(unsigned int Level) { m_Level = Level; }
	void SetPlyrGold(float Gold) { m_Gold = Gold; }
	void IncPlyrGold(float Gold) { m_Gold += Gold; }
	void DecPlyrGold(float Gold) { m_Gold = (m_Gold - Gold < 0) ? 0 : m_Gold -= Gold; }
	//Getters
	Item GetItem(std::string ItemName);
	int GetEXP() { return m_EXP; }
	Weapon GetWeapon() { return m_Equipped; }
	int GetAC() { return m_AC; }
	std::vector<Item> GetItems() { return m_PlyrItems; }
	std::string GetPlyrName() { return m_PlyrName; }
	unsigned int GetPlyrLevel() { return m_Level; }
	float GetPlyrGold() { return m_Gold; }
	int GetHP() { return m_HP; }
	int getMaxHP() { return m_MaxHP; }


	void UpdateHP(StatBlock);
	void AddEXP(int val);
	StatBlock RollStats();
	double Roll4d6();
	double Player::WeaponAttack(Weapon, Enemies);
	std::string BuildPath(std::string FilePath);
private:
	std::string m_PlyrName = "BLANK";
	std::vector<Item> m_PlyrItems;
	unsigned int m_Level = 1;
	float m_Gold = 0;

	StatBlock m_PC_Stats;
	int m_HP, m_MaxHP;
	int m_AC = 10;
	double m_Money = 50.00;
	int m_EXP = 0;
	bool m_level_up;
	int m_threshold_index = 0;
	int m_level_threshold[19] = { 300,900,2700,6500,14000,23000,34000,48000,64000,85000,100000,120000,140000,165000,195000,225000,265000,305000,355000 };
	Weapon m_Equipped = Weapon("Replica Dagger", "A Dagger you bought at a medieval fayre, you sharpened it yourself, badly, it seems mass produced.", 0, false, 5, 50);
	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};