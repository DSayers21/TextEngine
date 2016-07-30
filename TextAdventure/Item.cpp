#include "Item.h"

Item::Item(std::string ItmName, std::string ItmDesc, float ItmValue, bool Stackable)
{
	m_ItmName = ItmName;
	m_ItmDesc = ItmDesc;
	m_ItmValue = ItmValue;
	m_Stackable = Stackable;
}

Item::~Item()
{
	//Empty
}

Item::Item(const Item& other)
{
	m_ItmName = other.m_ItmName;
	m_ItmDesc = other.m_ItmDesc;
	m_ItmValue = other.m_ItmValue;
	m_Stackable = other.m_Stackable;
}

Item Item::operator=(const Item& other)
{
	m_ItmName = other.m_ItmName;
	m_ItmDesc = other.m_ItmDesc;
	m_ItmValue = other.m_ItmValue;
	m_Stackable = other.m_Stackable;
	return *this;
}