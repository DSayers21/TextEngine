#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ConsoleProp.h"
#include "InputControl.h"

class InputControl;

class COutput
{
public:
	COutput();

	COutput(ConsoleProp& Console, InputControl& Input);

	~COutput();

	void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL);

	void WriteSlow(std::string DisplayString, bool EndL);

	void WriteLine(int Colour, char WriteChar);

	void CompleteLine(char FinChar);

	void DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour);

	void ConsoleClear();

	std::vector<std::string> GetInput(std::string Question);

	//Setters
	void SetConsole(ConsoleProp& Console);

	void SetInput(InputControl& Input);

	//Getters
	ConsoleProp* GetConsole();

private:
	bool CheckIfOver(std::string DisplayString);

	void TypeString(std::string DisplayString);

	bool TestTag(std::string StringPassed);

	void SetTag(std::string StringPassed);

	ConsoleProp* _Console;

	InputControl* _Input;

	int _Speed;
};

