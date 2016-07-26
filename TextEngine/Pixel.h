#pragma once
class Pixel
{
public:
	Pixel();
	Pixel(int Colour);
	Pixel(int Colour, char Char);

	~Pixel();

	Pixel(const Pixel& other);
	Pixel operator=(const Pixel &other);

	void SetColour(int Colour);
	int GetColour();
	void SetChar(char Char);
	char GetChar();

private:
	int _Colour;
	char _Char;
};