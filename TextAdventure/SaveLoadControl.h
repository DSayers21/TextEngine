#pragma once
#include <boost/property_tree/ptree.hpp>
#include <vector>

#include <map>

class Location;
class Object;
class NPC;
class Item;

class SaveLoadControl
{
public:
	SaveLoadControl();

	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec);
	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item*> ItmVec);
	void SaveItemsToVector(std::vector<Item>* ItemVec, boost::property_tree::ptree& Items);
	void SaveItemsToVector(std::vector<Item*>* ItemVec, boost::property_tree::ptree& Items);


	void SaveLocationToTree(boost::property_tree::ptree* Locations, std::map<std::string, Location*> LocationMap);
	void SaveLocationToMap(boost::property_tree::ptree* Locations, std::map<std::string, Location*>* LocationMap);


	void SaveObjectsToVector(std::vector<Object*>* ObjectVec, boost::property_tree::ptree& Objects);
	void SaveObjectsToTree(boost::property_tree::ptree* Objects, std::vector<Object*> ObjectVec);


	void SaveNPCsToVector(std::vector<NPC*>* NPCVec, boost::property_tree::ptree& NPCs);
	void SaveNPCsToTree(boost::property_tree::ptree* NPCs, std::vector<NPC*> NPCVec);
};

