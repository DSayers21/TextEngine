#pragma once
#include <boost/property_tree/ptree.hpp>
#include <Vector>
#include <windows.h>
#include <stdio.h>
#include <map>
#include <stdexcept>

class Location;
class Object;
class NPC;
class Item;
class Weapon;
class Enemies;

class SaveLoadControl
{
public:
	SaveLoadControl()
	{

	}

	template <class T>
	void SaveVecToTree(boost::property_tree::ptree* Tree, std::vector<T>& Vec, std::string FilePath, std::string Type)
	{
		if (Vec.size() > 0)
		{
			//Loop through all the options
			for (int i = 0; i < Vec.size(); i++)
			{
				//Get the current option
				Vec[i].Save(FilePath);
				//Get the option number
				std::string TypeNum = Type + std::to_string(i);
				//Create the tree for the current option num
				boost::property_tree::ptree SubTree;
				//Put all the option information into the tree
				SubTree.put(Type + "Path", Vec[i].BuildPath(FilePath));
				//Add the current option num into the options tree
				Tree->add_child(TypeNum, SubTree);
			}
		}
	}
	template <class T>
	void SaveVecToTree(boost::property_tree::ptree* Tree, std::vector<T*>& Vec, std::string FilePath, std::string Type)
	{
		if (Vec.size() > 0)
		{
			//Loop through all the options
			for (int i = 0; i < Vec.size(); i++)
			{
				//Get the current option
				Vec[i]->Save(FilePath);
				//Get the option number
				std::string TypeNum = Type + std::to_string(i);
				//Create the tree for the current option num
				boost::property_tree::ptree SubTree;
				//Put all the option information into the tree
				SubTree.put(Type + "Path", Vec[i]->BuildPath(FilePath));
				//Add the current option num into the options tree
				Tree->add_child(TypeNum, SubTree);
			}
		}
	}
	template <class T>
	void SaveTreeToVector(std::vector<T>& Vec, boost::property_tree::ptree& Tree, std::string Type)
	{
		if (Tree.size() > 0)
		{
			for (int i = 0; i < Tree.size(); i++)
			{
				//Get options number child
				std::string Name = Type + std::to_string(i);
				boost::property_tree::ptree TypeNum = Tree.get_child(Name);
				//Get all information needed from optionNum
				std::string FilePath = TypeNum.get<std::string>(Type + "Path");
				//Add Item
				T LoadObject;
				LoadObject.Load(FilePath);
				Vec.push_back(LoadObject);
			}
		}
	}
	template <class T>
	void SaveTreeToVector(std::vector<T*>& Vec, boost::property_tree::ptree& Tree, std::string Type)
	{
		if (Tree.size() > 0)
		{
			for (int i = 0; i < Tree.size(); i++)
			{
				//Get options number child
				std::string Name = Type + std::to_string(i);
				boost::property_tree::ptree TypeNum = Tree.get_child(Name);
				//Get all information needed from optionNum
				std::string FilePath = TypeNum.get<std::string>(Type + "Path");
				//Add Item
				T* LoadObject = new T();
				LoadObject->Load(FilePath);
				Vec.push_back(LoadObject);
			}
		}
	}

	void CreateFolder(const char * path)
	{
		if (!CreateDirectory(path, NULL))
		{
			return;
		}
	}
};