#pragma once
#include <boost/property_tree/ptree.hpp>
#include <vector>
#include "Item.h"
#include "Location.h"
#include <map>

class SaveLoadControl
{
public:
	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec);
	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item*> ItmVec);
	void SaveItemsToVector(std::vector<Item>* ItemVec, boost::property_tree::ptree& Items);
	void SaveItemsToVector(std::vector<Item*>* ItemVec, boost::property_tree::ptree& Items);

	void SaveLocationToTree(boost::property_tree::ptree* Locations, std::map<std::string, Location*> LocationMap);
	void SaveLocationToMap(boost::property_tree::ptree* Locations, std::map<std::string, Location*>* LocationMap);
};

