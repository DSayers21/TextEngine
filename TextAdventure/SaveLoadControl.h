#pragma once
#include <boost/property_tree/ptree.hpp>
#include <vector>
#include "Item.h"

class SaveLoadControl
{
public:
	void SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec);
	void SaveItemsToVector(std::vector<Item>* ItemVec, boost::property_tree::ptree& Items);
};

