#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <boost/property_tree/ptree.hpp>
#include <TextEngine/COutput.h>

#include "SaveLoadControl.h"

#include "Item.h"
#include "Object.h"
#include "NPC.h"
#include "Player.h"

#include <string>
#include <map>
#include <vector>

class Object;
class NPC;
class Enemies;

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
	Object* FindObject(std::string ObjName);
	NPC* FindNPC(std::string NPCName);
	Enemies* FindEnemy(std::string EnemyName);
	std::string GetImage() { return m_LocationImage; }

	//Setters
	void SetName(std::string Name) { m_Name = Name; }
	void SetDesc(std::string Desc) { m_Desc = Desc; }
	void SetLocationNum(std::string LocationNum) { m_LocationNum = LocationNum; }

	bool HasImage() { return (m_LocationImage == "") ? false : true; }

	std::string BuildPath(std::string FilePath);

	void Load(std::string FilePath);
	void Save(std::string FilePath, std::string Num);

	void AddExit(std::string Direction, Location *Loc);
	void AddItem(Item Itm);
	void AddWeapon(Weapon Wpn);
	void AddObject(Object *Obj);
	void AddNPC(NPC *npc);
	void AddEnemy(Enemies Enmy);

	void RemEnemy();	//removes enemy if it falls to 0HP after the end of a battle

	void DisplayAll(TxtEgn::COutput* Output);
	std::string DisplayExits(TxtEgn::COutput* Output);
	std::string DisplayItems(TxtEgn::COutput* Output);
	std::string DisplayWeapons(TxtEgn::COutput* Output);
	std::string DisplayObjects(TxtEgn::COutput* Output);
	std::string DisplayNPCs(TxtEgn::COutput* Output);
	std::string DisplayEnemies(TxtEgn::COutput* Output);

	Location* GoCommand(std::string Direction);

	std::string BuildPath(std::string FilePath, std::string LocationNum);
	std::string BuildPathLocNum(std::string FilePath);

	void PickUpItem(TxtEgn::COutput* Output, Player* Plr, std::string ItemName);

	bool InspectAll(TxtEgn::COutput* Output, std::string Compare);
	bool InspectItems(TxtEgn::COutput* Output, std::string Compare);
	bool InspectWeapons(TxtEgn::COutput* Output, std::string Compare);
	bool InspectObjects(TxtEgn::COutput* Output, std::string Compare);
	bool InspectNPCs(TxtEgn::COutput* Output, std::string Compare);

	void CommandObject(TxtEgn::COutput* Output, GameWorld* Game, std::string Command, std::string InitialString, Player* Plr);
	std::vector<std::string> Location::GetObjectFrString(std::string InitialString);

	void GivetoNPC(std::string Command, TxtEgn::COutput* Output, Player* Plr);

private:
	NPC* InRoomNPC(std::string NPCName);
	void GiveCommand(std::string Command, std::string ItemName, TxtEgn::COutput* Output, Player* Plr);

	std::string m_Name;
	std::string m_Desc;

	std::string m_LocationImage = "BLANK";

	std::map<std::string, Location*> m_Exits = std::map<std::string, Location*>();

	std::vector<Item> m_Items;
	std::vector<Weapon> m_Weapons;
	std::vector<Enemies> m_Enemies;
	std::vector<Object*> m_Objects;
	std::vector<NPC*> m_NPC;

	std::string m_LocationNum;


	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

