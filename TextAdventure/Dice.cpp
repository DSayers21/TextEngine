#include "Dice.h"

Dice::Dice(unsigned int Sides) : m_sides(Sides) {}

Dice::~Dice()
{
}

unsigned int Dice::Roll()
{
	int temp = rand() % m_sides + 1;
	srand(time(NULL));
	return temp;

}
