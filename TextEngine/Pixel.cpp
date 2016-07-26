#include "Pixel.h"

Pixel::Pixel() : _Colour(7), _Char(' ')
{
}

Pixel::Pixel(int Colour) : _Char(' ')
{
	_Colour = Colour;
}

Pixel::Pixel(int Colour, char Char)
{
	_Colour = Colour;
	_Char = Char;
}

Pixel::~Pixel()
{
}

Pixel::Pixel(const Pixel& other)
{
	_Colour = other._Colour;
	_Char = other._Char;
}

Pixel Pixel::operator=(const Pixel &other)
{
	_Colour = other._Colour;
	_Char = other._Char;
	return *this;
}

void Pixel::SetColour(int Colour)
{
	_Colour = Colour;
}

int Pixel::GetColour()
{
	return _Colour;
}

void Pixel::SetChar(char Sent)
{
	_Char = Sent;
}

char Pixel::GetChar()
{
	return _Char;
}