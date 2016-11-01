#pragma once

namespace TxtEgn
{
	class Pixel
	{
	public:
		//Constructir
		Pixel();
		//Constructor with colour
		Pixel(int Colour);
		//Constructor with colour and char
		Pixel(int Colour, char Char);
		//Destructor
		~Pixel();
		//Copy Constructor
		Pixel(const Pixel& other);
		//Equals operator
		Pixel operator=(const Pixel &other);

		//Getters
		//Returns the colour of the Pixel
		int GetColour(){ return _Colour; }
		//Returns the associated char of the Pixel
		char GetChar(){ return _Char; }

		//Setters
		//Sets the colour of the Pixel
		void SetColour(int Colour) { _Colour = Colour; }
		//Sets the associated char of the Pixel
		void SetChar(char Sent) { _Char = Sent; }

	private:
		//Colour of the Pixel
		int _Colour;
		//Char of the Pixel
		char _Char;
	};
}