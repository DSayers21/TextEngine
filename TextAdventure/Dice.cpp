#include "Dice.h"



Dice::Dice()
{
}


Dice::~Dice()
{
}

int Battle::RollD20()
{
	int temp = rand() % 20 + 1;
	srand(time(NULL));
	return temp;
}
