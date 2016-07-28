#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

class InOutDataManager
{
public:
	InOutDataManager();
	~InOutDataManager();

	void SaveJSON(std::string FilePath, boost::property_tree::ptree Tree);
	void SaveXML(std::string FilePath, boost::property_tree::ptree Tree);

	boost::property_tree::ptree LoadJSON(std::string FilePath);
	boost::property_tree::ptree* LoadXML(std::string FilePath);
};


