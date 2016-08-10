#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"
#include <vector>
#include <string>

class Location;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Load(std::string FilePath);

	void Save(std::string FilePath);

private:
	std::vector<Location*> m_Locations;

	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

