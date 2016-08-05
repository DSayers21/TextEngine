#pragma once
#include <string>
#include <vector>
#include <TextEngine/InputControl.h>

class Item;

class Player
{
public:
	Player(std::string PlyrName, unsigned int Level, float Gold);
	~Player();

	void AddItem(Item* addItem);
	void RemoveItem(Item* remItem);

	//Setters
	void SetPlyrName(std::string PlyrName) { m_PlyrName = PlyrName; }
	void SetPlyrLevel(unsigned int Level) { m_Level = Level; }
	void SetPlyrGold(float Gold) { m_Gold = Gold; }
	void IncPlyrGold(float Gold) { m_Gold += Gold; }
	void DecPlyrGold(float Gold) { m_Gold = (m_Gold - Gold < 0) ? 0 : m_Gold -= Gold; }
	//Getters
	Item* GetItem(std::string ItemName);
	std::string GetPlyrName() { return m_PlyrName; }
	unsigned int GetPlyrLevel() { return m_Level; }
	float GetPlyrGold() { return m_Gold; }
private:

	std::string m_PlyrName = "John Doe";
	std::vector<Item*> m_PlyrItems;
	unsigned int m_Level = 1;
	float m_Gold = 0;

	TxtEgn::InputControl m_Input;
};

