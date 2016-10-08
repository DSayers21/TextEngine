#pragma once
#include <cstdlib>
#include <ctime>
class Dice
{
public:
	Dice(unsigned int Sides);
	~Dice();

	unsigned int Roll();
private:
	unsigned int m_sides;
};

