#pragma once

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

	enum class ALIGN {
		LEFT,
		CENTER,
		RIGHT,
	};

	class COutput
	{
	public:
		COutput();

		COutput(ConsoleProp& Console, InputControl& Input, ImageCache& Cache);

		~COutput();

		void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL);

		void WriteSlow(std::string DisplayString, bool EndL, 
			ALIGN Align = ALIGN::LEFT, bool CompLine = false);

		void WriteLine(int Colour, char WriteChar);

		void CompleteLine(char FinChar);

		void DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour);

		void ConsoleClear();

		void ConsoleClearLine();

		std::vector<std::string> GetInput(std::string Question);

		void DrawImage(std::string Img, ALIGN Align);

		void DisplayColumns3(std::string Left, std::string Middle, std::string Right, int Colour, ALIGN Align);
		
		void COutput::DisplayColumnsConvo(std::string Left, std::string Right, int ColourA, int ColourB, ALIGN Align);

		int MenuOptions(std::vector<std::string> OptionList);

		//Setters
		void SetConsole(ConsoleProp& Console);

		void SetInput(InputControl& Input);

		//Getters
		ConsoleProp* GetConsole();

	private:
		bool CheckIfOver(std::string DisplayString);

		void TypeString(std::string DisplayString);
		void DisplayLine(std::string Line, int LineLength, ALIGN Align, bool CompLine);

		void DisplayAll(std::vector<std::string> Lines, std::vector<int> LineLengths, 
			bool EndL, ALIGN Align, bool CompLine);
		

		//Tags
		int TestTag(std::string StringPassed);
		void SetTag(std::string StringPassed);

		//Columns
		COutput CreateColumn(int Width, int StartX, int Colour);
		int DisplayColumn(std::string Statement, int LowestY, ALIGN Align);
		
		//Align
		int ImageAlign(ASCImage Img, ALIGN Align);
		int AlignString(int Buffer, ALIGN Align);

		//Member Variables

		ConsoleProp* _Console;

		InputControl* _Input;

		ImageCache* _Cache;

		int _Speed = 30;
	};
}