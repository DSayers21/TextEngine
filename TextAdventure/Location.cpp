#include "Location.h"



Location::Location(std::string Name, std::string Desc) : m_Name(Name), m_Desc(Desc)
{
}


Location::~Location()
{
}

std::string Location::BuildPath()
{
	return "Location/" + m_Name;
}

void Load(std::string FilePath)
{

}

void Save(std::string FilePath)
{

}