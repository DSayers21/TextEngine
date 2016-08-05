#include "SaveLoadControl.h"

void SaveLoadControl::SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec)
{
	if (ItmVec.size() > 0)
	{
		//Loop through all the options
		for (int i = 0; i < ItmVec.size(); i++)
		{
			//Get the current option
			Item* Current = &ItmVec[i];
			//Get the option number
			std::string ItmNum = "Item" + std::to_string(i);
			//Create the tree for the current option num
			boost::property_tree::ptree ItemTree;
			//Put all the option information into the tree
			ItemTree.put("ItmPath", Current->GetItemPath());
			//Add the current option num into the options tree
			Items->add_child(ItmNum, ItemTree);
		}
	}
}

void SaveLoadControl::SaveItemsToVector(std::vector<Item>* ItemVec, boost::property_tree::ptree& Items)
{
	for (int j = 0; j < Items.size(); j++)
	{
		//Get options number child
		std::string ItemName = "Item" + std::to_string(j);
		boost::property_tree::ptree ItemNum = Items.get_child(ItemName);
		//Get all information needed from optionNum
		std::string FilePath = ItemNum.get<std::string>("ItmPath");

		//Add Item
		Item loadItem;
		loadItem.Load(FilePath);
		ItemVec->push_back(loadItem);
	}
}