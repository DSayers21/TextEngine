#pragma once
#include <string>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/InputControl.h>
#include <boost/property_tree/ptree.hpp>


class Item
{
public:
	Item();
	Item(std::string ItmName, std::string ItmDesc, float ItmValue, bool Stackable);
	~Item();
	Item(const Item& other);
	Item operator=(const Item& other);
	//Setters
	void SetItemName(std::string ItmName) { m_ItmName = ItmName; }
	void SetItemDesc(std::string ItmDesc) { m_ItmDesc = ItmDesc; }
	void SetItemValue(float ItmValue) { m_ItmValue = ItmValue; }
	void SetFilePath() { m_ItmPath = "Item/" + m_Input.RemoveSpaces(m_ItmName); }

	//Getters
	std::string GetItemName() { return m_ItmName; }
	std::string GetItemDesc() { return m_ItmDesc; }
	float GetItemValue() { return m_ItmValue; }
	bool IfStackable() { return m_Stackable; }
	std::string GetItemPath() { return m_ItmPath; }

	//SaveNLoad
	void Load(std::string FilePath);
	void Save();

private:
	std::string m_ItmPath = "FilePath";
	std::string m_ItmName = "EmptyItem";
	std::string m_ItmDesc = "EmptyDesc";
	float m_ItmValue = 0.0f;
	bool m_Stackable = false;

	TxtEgn::InputControl m_Input;
	InOutDataManager m_IOMan;
};