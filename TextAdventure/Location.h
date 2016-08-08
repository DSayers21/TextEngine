#pragma once
#include <TextEngine/InputControl.h>
#include <TextEngine/InOutDataManager.h>
#include <boost/property_tree/ptree.hpp>
#include "SaveLoadControl.h"

#include <string>
#include <map>
#include <vector>


class Location
{
public:
	Location(std::string Name, std::string Desc);
	~Location();

	//Getters
	std::string GetName() { return m_Name; }
	std::string GetDesc() { return m_Desc; }

	//Setters
	void SetName(std::string Name) { m_Name = Name; }
	void SetDesc(std::string Desc) { m_Desc = Desc; }

	std::string BuildPath();

	void Load(std::string FilePath);
	void Save(std::string FilePath);

private:
	std::string m_Name;
	std::string m_Desc;

	TxtEgn::InputControl m_Input;
	SaveLoadControl m_SandL;
	InOutDataManager m_IOMan;
};

