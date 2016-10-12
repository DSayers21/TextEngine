#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>

#include <boost/property_tree/ptree.hpp>

#include "SaveLoadControl.h"

#include <vector>
#include <string>

class Location;
class Player;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Load(std::string FilePath);

	void Save(std::string FilePath, Player* Plr);

	Location* GetFirstLocation() { return m_Locations[0]; }

	Location* FindLocation(std::string LocName);

	std::string GetImage() { return m_Image; }

private:
	void CreateFolder(std::string Path);

	std::vector<Location*> m_Locations;

	std::string m_GameName;
	std::string m_Image = "BLANK";

	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};