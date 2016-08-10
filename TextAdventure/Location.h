#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"

#include "Item.h"
#include "Object.h"
#include "NPC.h"

#include <string>
#include <map>
#include <vector>

class Object;
class NPC;
class Location
{
public:
	Location();
	Location(std::string Name, std::string Desc);
	~Location();

	//Getters
	std::string GetName() { return m_Name; }
	std::string GetDesc() { return m_Desc; }
	std::string GetLocationNum() { return m_LocationNum; }
	std::map<std::string, Location*> GetExits() { return m_Exits; }

	//Setters
	void SetName(std::string Name) { m_Name = Name; }
	void SetDesc(std::string Desc) { m_Desc = Desc; }
	void SetLocationNum(std::string LocationNum) { m_LocationNum = LocationNum; }


	std::string BuildPath(std::string FilePath);

	void Load(std::string FilePath);
	void Save(std::string FilePath, std::string Num);

	void AddExit(std::string Direction, Location *Loc);

	void DisplayAll();

	std::string BuildPath(std::string FilePath, std::string LocationNum);
	std::string BuildPathLocNum(std::string FilePath);

private:
	std::string m_Name;
	std::string m_Desc;

	std::map<std::string, Location*> m_Exits = std::map<std::string, Location*>();

	std::vector<Item> m_Items;
	std::vector<Object*> m_Objects;
	std::vector<NPC*> m_NPC;

	std::string m_LocationNum;


	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

