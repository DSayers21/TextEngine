#pragma once

//Includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

class InOutDataManager
{
public:
	//Constructor
	InOutDataManager();
	//Destructor
	~InOutDataManager();

	//Save a tree to either xml or json depending on the extension variables
	void SaveFile(std::string FilePath, boost::property_tree::ptree& Tree);
	//Load a xml of json depending on extension vairables into a tree and then return it
	boost::property_tree::ptree LoadFile(std::string FilePath);

private:
	//Save a tree to JSON
	void SaveJSON(std::string FilePath, boost::property_tree::ptree& Tree);
	//Save a tree to XML
	void SaveXML(std::string FilePath, boost::property_tree::ptree& Tree);
	//Load a tree from JSON
	boost::property_tree::ptree LoadJSON(std::string FilePath);
	//Load a tree from XML
	boost::property_tree::ptree LoadXML(std::string FilePath);
	//Save and Load extensions
	std::string SaveExtension = ".xml";
	std::string LoadExtension = ".xml";
};