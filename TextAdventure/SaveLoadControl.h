#pragma once
#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <map>

class Location;
class Object;
class NPC;
class Item;

class SaveLoadControl
{
public:
	SaveLoadControl();

	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec, std::string FilePath);
	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item*> ItmVec, std::string FilePath);
	void SaveItemsToVector(std::vector<Item>* ItemVec, boost::property_tree::ptree& Items);
	void SaveItemsToVector(std::vector<Item*>* ItemVec, boost::property_tree::ptree& Items);


	void SaveLocationToTree(boost::property_tree::ptree* Locations, std::map<std::string, Location*> LocationMap, std::string FilePath);
	void SaveLocationToMap(boost::property_tree::ptree* Locations, std::map<std::string, Location*>* LocationMap);


	void SaveObjectsToVector(std::vector<Object*>* ObjectVec, boost::property_tree::ptree& Objects);
	void SaveObjectsToTree(boost::property_tree::ptree* Objects, std::vector<Object*> ObjectVec, std::string FilePath);


	std::vector<NPC*> SaveNPCsToVector(std::vector<NPC*> NPCVec, boost::property_tree::ptree& NPCs);
	void SaveNPCsToTree(boost::property_tree::ptree* NPCs, std::vector<NPC*> NPCVec, std::string FilePath);

	void CreateFolder(const char * path)
	{
		if (!CreateDirectory(path, NULL))
		{
			return;
		}
	}
};

