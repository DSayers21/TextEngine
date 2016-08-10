#include "SaveLoadControl.h"
#include "Object.h"
#include "NPC.h"
#include "Location.h"
#include "Item.h"

SaveLoadControl::SaveLoadControl()
{

}

//Items

void SaveLoadControl::SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item>& ItmVec, std::string FilePath)
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
			ItemTree.put("ItmPath", Current->BuildPath(FilePath));
			//Add the current option num into the options tree
			Items->add_child(ItmNum, ItemTree);
		}
	}
}
void SaveLoadControl::SaveItemsToTree(boost::property_tree::ptree* Items, std::vector<Item*> ItmVec, std::string FilePath)
{
	if (ItmVec.size() > 0)
	{
		//Loop through all the options
		for (int i = 0; i < ItmVec.size(); i++)
		{
			//Get the current option
			Item* Current = ItmVec[i];
			//Get the option number
			std::string ItmNum = "Item" + std::to_string(i);
			//Create the tree for the current option num
			boost::property_tree::ptree ItemTree;
			//Put all the option information into the tree
			ItemTree.put("ItmPath", Current->BuildPath(FilePath));
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
void SaveLoadControl::SaveItemsToVector(std::vector<Item*>* ItemVec, boost::property_tree::ptree& Items)
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
		ItemVec->push_back(&loadItem);
	}
}

//Location

void SaveLoadControl::SaveLocationToTree(boost::property_tree::ptree* Locations, std::map<std::string, Location*> LocationMap, std::string FilePath)
{
	int Count = 0;
	for (std::map<std::string, Location*>::iterator ii = LocationMap.begin(); ii != LocationMap.end(); ++ii)
	{
		//Get the current location
		Location* Current = ii->second;
		//Get the option number
		std::string LocNum = "Location" + std::to_string(Count);
		//Create the tree for the current option num
		boost::property_tree::ptree LocationTree;
		//Put all the option information into the tree
		LocationTree.put("ItmPath", Current->BuildPath());
		LocationTree.put("Direction", ii->first);
		//Add the current option num into the options tree
		Locations->add_child(LocNum, LocationTree);
		Count++;
	}
}

void SaveLoadControl::SaveLocationToMap(boost::property_tree::ptree* Locations, std::map<std::string, Location*>* LocationMap)
{
	for (int i = 0; i < Locations->size(); i++)
	{
		//Get options number child
		std::string LocationName = "Location" + std::to_string(i);
		boost::property_tree::ptree LocationNum = Locations->get_child(LocationName);
		//Get all information needed from optionNum
		std::string FilePath = LocationNum.get<std::string>("ItmPath");
		std::string Direction = LocationNum.get<std::string>("Direction");
		//Add Location
		Location loadLocation;
		loadLocation.Load(FilePath);
		LocationMap->insert(std::pair<std::string, Location*>(Direction, &loadLocation));
	}
}

//Object

void SaveLoadControl::SaveObjectsToVector(std::vector<Object*>* ObjectVec, boost::property_tree::ptree& Objects)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		//Get options number child
		std::string ObjectName = "Object" + std::to_string(i);
		boost::property_tree::ptree ObjectNum = Objects.get_child(ObjectName);
		//Get all information needed from optionNum
		std::string FilePath = ObjectNum.get<std::string>("ObjectPath");

		//Add Object
		Object loadObject;
		//loadObject.LoadObject(FilePath);
		ObjectVec->push_back(&loadObject);
	}
}
void SaveLoadControl::SaveObjectsToTree(boost::property_tree::ptree* Objects, std::vector<Object*> ObjectVec, std::string FilePath)
{
	//Loop through all the options
	for (int i = 0; i < ObjectVec.size(); i++)
	{
		//Get the current option
		Object* Current = ObjectVec[i];
		//Get the option number
		std::string ObjectNum = "Object" + std::to_string(i);
		//Create the tree for the current option num
		boost::property_tree::ptree ObjectTree;
		//Put all the option information into the tree
		ObjectTree.put("ObjectPath", Current->BuildPath(FilePath));
		//Add the current option num into the options tree
		Objects->add_child(ObjectNum, ObjectTree);
	}
}


//NPC

void SaveLoadControl::SaveNPCsToVector(std::vector<NPC*>* NPCVec, boost::property_tree::ptree& NPCs)
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		//Get options number child
		std::string NPCName = "NPC" + std::to_string(i);
		boost::property_tree::ptree NPCNum = NPCs.get_child(NPCName);
		//Get all information needed from optionNum
		std::string FilePath = NPCNum.get<std::string>("NPCPath");

		//Add Item
		NPC loadNPC;
		loadNPC.Load(FilePath);
		NPCVec->push_back(&loadNPC);
	}
}

void SaveLoadControl::SaveNPCsToTree(boost::property_tree::ptree* NPCs, std::vector<NPC*> NPCVec, std::string FilePath)
{
	//Loop through all the options
	for (int i = 0; i < NPCVec.size(); i++)
	{
		//Get the current option
		NPC* Current = NPCVec[i];
		//Get the option number
		std::string NPCNum = "NPC" + std::to_string(i);
		//Create the tree for the current option num
		boost::property_tree::ptree NPCTree;
		//Put all the option information into the tree
		NPCTree.put("NPCPath", Current->BuildPath(FilePath));
		//Add the current option num into the options tree
		NPCs->add_child(NPCNum, NPCTree);
	}
}