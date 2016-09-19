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

		void WriteSlow(std::string DisplayString, bool EndL);

		void WriteLine(int Colour, char WriteChar);

		void CompleteLine(char FinChar);

		void DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour);

		void ConsoleClear();

		std::vector<std::string> GetInput(std::string Question);

		void DrawImage(std::string Img, ALIGN Align);

		void DisplayColumns3(std::string Left, std::string Middle, std::string Right, int Colour);
		
		void COutput::DisplayColumnsConvo(std::string Left, std::string Right, int ColourA, int ColourB);

		COutput CreateColumn(int Width, int StartX, int Colour);

		int DisplayColumn(std::string Statement, int LowestY);

		//Setters
		void SetConsole(ConsoleProp& Console);

		void SetInput(InputControl& Input);

		//Getters
		ConsoleProp* GetConsole();

	private:
		bool CheckIfOver(std::string DisplayString);

		void TypeString(std::string DisplayString);

		int TestTag(std::string StringPassed);

		void SetTag(std::string StringPassed);

		int ImageAlign(ASCImage Img, ALIGN Align);

		ConsoleProp* _Console;

		InputControl* _Input;

		ImageCache* _Cache;

		int _Speed;
	};
}