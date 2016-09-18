#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <TextEngine/COutput.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"

#include <string>
#include <map>
#include <vector>

class Location;
class Item; 
class GameWorld;
class Player;

class Object
{
public:
	Object();
	Object(std::string Name, std::string Desc, 
		std::string ActionWord, std::string m_RemovedDesc, std::string m_ActionConnector = "");

	~Object();

	void AddExit(std::string Direction, std::string Room);

	void AddItem(Item* sItem);
	void RemoveItem(std::string ItmName);

	//Getters
	std::string GetName() { return m_Name; }
	std::string GetDesc() { return m_Desc; }
	std::string GetActionWord() { return m_ActionWord; }
	std::string GetActionConnector() { return m_ActionConnector; }
	std::string GetRemovedDesc() { return m_RemovedDesc; }
	std::string GetActionItemName() { return m_ActionItemName; }
	bool IfRemoved() { return m_IfRemoved; }

	//Setters
	void SetRemoved(bool Removed) { m_IfRemoved = Removed; }
	void SetActionItemName(std::string ActionItemName) { m_ActionItemName = ActionItemName; };

	//SaveAndLoad
	void Save(std::string FilePath);
	void Load(std::string FilePath);

	std::string BuildPath(std::string FilePath);

	void ObjectCommand(TxtEgn::COutput* Output, GameWorld* Game, std::string Command, Player* MainPlr, Location* Current);
	void Object::ObjectAction(TxtEgn::COutput* Output, GameWorld* Game, Location* Current);

private:
	std::string m_Name = "Blank";
	std::string m_Desc = "Blank";

	std::string m_ActionWord = "Blank";				//e.g. Unlock, Search, Use, push, pull
	std::string m_ActionConnector = "Blank";		//e.g. with, using, to, and
	std::string m_RemovedDesc = "Blank";			//The message which appears when the object is interacted with
	std::string m_ActionItemName = "Blank";			//e.g key, card, token etc

	std::map<std::string, std::string> m_NewExits = std::map<std::string, std::string>();	//Exits which get added to the current location when the object has been moved
	std::vector<Item*> m_NewItems;														//Items which get added to the room, e.g. they fall to the floor after the door is opened
	
	bool m_IfRemoved = false;

	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

