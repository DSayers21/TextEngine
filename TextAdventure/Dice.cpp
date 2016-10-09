#include "Dice.h"
#include <random>

Dice::Dice()
{

}
Dice::Dice(unsigned int Sides) : m_sides(Sides) {}

Dice::~Dice()
{
}

unsigned int Dice::Roll()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> die(1, m_sides); // distribution in range [1, 6]

	return die(rng);
}