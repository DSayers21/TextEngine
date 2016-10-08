#pragma once
#include <string>
#include <vector>
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/COutput.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"

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
	void SetPlyrLevel(unsigned int Level) { m_Level = Level; }
	void SetPlyrGold(float Gold) { m_Gold = Gold; }
	void IncPlyrGold(float Gold) { m_Gold += Gold; }
	void DecPlyrGold(float Gold) { m_Gold = (m_Gold - Gold < 0) ? 0 : m_Gold -= Gold; }
	//Getters
	Item GetItem(std::string ItemName);
	std::vector<Item> GetItems() { return m_PlyrItems; }
	std::string GetPlyrName() { return m_PlyrName; }
	unsigned int GetPlyrLevel() { return m_Level; }
	float GetPlyrGold() { return m_Gold; }
	int GetHP() { return HP; }

	std::string BuildPath(std::string FilePath);
private:
	std::string m_PlyrName = "BLANK";
	std::vector<Item> m_PlyrItems;
	unsigned int m_Level = 1;
	float m_Gold = 0;

	int HP, MaxHP;

	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};