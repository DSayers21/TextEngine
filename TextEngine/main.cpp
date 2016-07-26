#include "ConsoleProp.h"
#include "COutput.h"
#include "InputControl.h"
#include "ConsoleZone.h"
#include "ImageCache.h"

#include <iostream>

int main()
{
	InputControl _Input;
	ImageCache Cache(_Input);

	ConsoleZone _ConsoleZoneA;
	ConsoleProp _Console;

	//_ConsoleZoneA.Init(50, 0, 7, 7, 10, 16, 12); 
	//_Console.Init(10, 16, 0, 0, 7, true);
	_Console.Init(16, 22, 0, 0, 7, true);
	_Console.SetConsoleWidth(_Console.FindConsoleWidth());

	//COutput _OutputA(_ConsoleZoneA, _Input, Cache);
	COutput _OutputB(_Console, _Input, Cache);
	
	_OutputB.DrawImage("Images/MafiaDen.txt", ALIGN::CENTER);
	_OutputB.DrawImage("Images/MainTitle.txt", ALIGN::LEFT);
	_OutputB.DrawImage("Images/MainTitle.txt", ALIGN::RIGHT);

	_OutputB.WriteSlow("<C123> Hello <C12> my name <C/> is ", true);

	int a;
	std::cin >> a;

	return 0;
}