#pragma once

namespace TxtEgn
{
	class Pixel
	{
	public:
		Pixel();
		Pixel(int Colour);
		Pixel(int Colour, char Char);

		~Pixel();

		Pixel(const Pixel& other);
		Pixel operator=(const Pixel &other);

		//Getters
		int GetColour(){ return _Colour; }
		char GetChar(){ return _Char; }

		//Setters
		void SetColour(int Colour) { _Colour = Colour; }
		void SetChar(char Sent) { _Char = Sent; }

	private:
		int _Colour;
		char _Char;
	};
}