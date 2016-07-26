#include "ConsoleProp.h"
#include "COutput.h"
#include "InputControl.h"
#include "ConsoleZone.h"

#include <iostream>

int main()
{
	InputControl _Input;

	ConsoleZone _ConsoleZoneA;
	ConsoleZone _ConsoleZoneB;

	_ConsoleZoneA.Init(50, 0, 7, 7, 10, 16, 12);
	_ConsoleZoneB.Init(50, 52, 7, 7, 10, 16, 13);

	std::cout << " Line " << std::endl;
	std::cout << " Line " << std::endl;
	std::cout << " Line " << std::endl;
	std::cout << " Line " << std::endl;
	std::cout << " Line " << std::endl;
	std::cout << " Line " << std::endl;

	COutput _OutputA(_ConsoleZoneA, _Input);
	COutput _OutputB(_ConsoleZoneB, _Input);

	_OutputA.DisplayBanner(_OutputA.GetConsole()->GetColour(), _Input.AlignCenter(' ', _OutputA.GetConsole()->GetConsoleWidth(), "Para 1"), true);
	for (int i = 0; i < 12; i++)
	{
		_OutputA.WriteSlow("The Quick Brown Fox Jumped Over The Lazy Dog", true);
	}
	
	_OutputB.DisplayBanner(_OutputB.GetConsole()->GetColour(), _Input.AlignLeft(' ', _OutputB.GetConsole()->GetConsoleWidth(),  "Para 2"), true);
	for (int i = 0; i < 21; i++)
	{
		_OutputB.WriteSlow("The Quick Brown Fox Jumped Over The Lazy Dog", true);
	}
	_OutputA.GetInput("What's your name?");
	_OutputB.GetInput("What's your second name?");
	_OutputA.WriteSlow("Deans Great", false);

	_OutputB.ConsoleClear();

	int a;
	std::cin >> a;

	return 0;
}