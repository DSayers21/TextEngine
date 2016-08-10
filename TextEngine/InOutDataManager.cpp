#include "InOutDataManager.h"



InOutDataManager::InOutDataManager()
{
}


InOutDataManager::~InOutDataManager()
{
}

void InOutDataManager::SaveFile(std::string FilePath, boost::property_tree::ptree& Tree)
{
	if (SaveExtension == ".xml")
		SaveXML(FilePath, Tree);
	else if (SaveExtension == ".json")
		SaveJSON(FilePath, Tree);
	else
		return;
}

boost::property_tree::ptree InOutDataManager::LoadFile(std::string FilePath)
{
	boost::property_tree::ptree Tree;
	if (LoadExtension == ".xml")
		Tree = LoadXML(FilePath);
	else if (LoadExtension == ".json")
		Tree = LoadJSON(FilePath);
	return Tree;
}

void InOutDataManager::SaveJSON(std::string FilePath, boost::property_tree::ptree& Tree)
{
	FilePath += ".json";
	boost::property_tree::write_json(FilePath, Tree);
}

void InOutDataManager::SaveXML(std::string FilePath, boost::property_tree::ptree& Tree)
{
	boost::property_tree::xml_writer_settings<std::string> Settings('\t', 1);
	FilePath += ".xml";
	boost::property_tree::write_xml(FilePath, Tree, std::locale(), Settings);
}

boost::property_tree::ptree InOutDataManager::LoadJSON(std::string FilePath)
{
	boost::property_tree::ptree Tree;
	FilePath += ".json";
	boost::property_tree::read_json(FilePath, Tree);
	return Tree;
}

boost::property_tree::ptree InOutDataManager::LoadXML(std::string FilePath)
{
	boost::property_tree::ptree Tree;
	FilePath += ".xml";
	boost::property_tree::read_xml(FilePath, Tree);
	return Tree;
}