#pragma once

//Includes
#include <iostream>
#include <string>
#include <vector>
#include "ConsoleProp.h"
#include "InputControl.h"
#include "ImageCache.h"
#include "ASCImage.h"

namespace TxtEgn
{
	class InputControl;

	//Align enum class, used for text and image alignment
	enum class ALIGN {
		LEFT,
		CENTER,
		RIGHT,
	};

	class COutput
	{
	public:
		//Constructor
		COutput();
		//Overloaded Constructor
		COutput(ConsoleProp& Console, InputControl& Input, ImageCache& Cache);
		//Destructor
		~COutput();
		//Displays a string without delay between characters.
		void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL);
		//Main Write function, displays a string which can be aligned on the consoleProp
		void WriteSlow(std::string DisplayString, bool EndL, 
			ALIGN Align = ALIGN::LEFT, bool CompLine = false);
		//Writes a line of characters across the screen (like a break line)
		void WriteLine(int Colour, char WriteChar);
		//Completes the current line with a defined character
		void CompleteLine(char FinChar);
		//Displays a vector of strings in a box which is composed of a character 'Surround'
		void DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour);
		//Clears the entire console
		void ConsoleClear();
		//Clears the current line of the console
		void ConsoleClearLine();
		//Gets user input from console
		std::vector<std::string> GetInput(std::string Question);
		//Draws image with a certain alignment
		void DrawImage(std::string Img, ALIGN Align);
		//Displays 3 strings in 3 columns next to one another
		void DisplayColumns3(std::string Left, std::string Middle, std::string Right, int Colour, ALIGN Align);
		//Displays two strings in columns next to each other with the left column being much shorter than the right
		void COutput::DisplayColumnsConvo(std::string Left, std::string Right, int ColourA, int ColourB, ALIGN Align);
		//Compares user input against vector of strings to determin which option was chosen
		int MenuOptions(std::vector<std::string> OptionList);

		//Setters
		//Sets the consoleProp which this an object of this class interfaces with
		void SetConsole(ConsoleProp& Console);
		//Sets the InputControl which this an object of this class interfaces with
		void SetInput(InputControl& Input);

		//Getters
		//Returns the consoleProp which this class interfaces with
		ConsoleProp* GetConsole();

	private:
		//Checks if a string if typed would or would not fit in the current row of the consoleProp
		bool CheckIfOver(std::string DisplayString);
		
		///Typing out Methods
		//Types out each line in the current buffer each with an alignemnt
		void DisplayAll(std::vector<std::string> Lines, std::vector<int> LineLengths, 
			bool EndL, ALIGN Align, bool CompLine);
		//Types out each string in the calculated current line with a certain alignment
		void DisplayLine(std::string Line, int LineLength, ALIGN Align, bool CompLine);
		//Types a string onto the console with a delay between characters
		void TypeString(std::string DisplayString);
		///End of typing out methods

		//Tests if a string contains a colour tag or not e.g. <C123> 
		int TestTag(std::string StringPassed);
		//Takes a tag e.g. <C123> and sets the colour appropriatly
		void SetTag(std::string StringPassed);

		//Returns an COutput for a new column, this way the console can be split
		COutput CreateColumn(int Width, int StartX, int Colour);
		//Displays a string with a certain alignment within a column
		int DisplayColumn(std::string Statement, int LowestY, ALIGN Align);
		
		//Retuns the padding needed before an image with a certain alignment
		int ImageAlign(ASCImage Img, ALIGN Align);
		//Retuns the padding needed before a length of a string with a certain alignment
		int AlignString(int Buffer, ALIGN Align);

		//Member Variables
		//Console which this COuput interfaces with
		ConsoleProp* _Console;
		//InputControl which this COuput interfaces with
		InputControl* _Input;
		//Cache of images which this COuput draws from
		ImageCache* _Cache;
		//Length of delay between characters
		int _Speed = 30;
	};
}