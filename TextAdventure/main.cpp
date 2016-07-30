#include <TextEngine/ConsoleProp.h>
#include <TextEngine/COutput.h>
#include <TextEngine/InputControl.h>
#include <TextEngine/ConsoleZone.h>
#include <TextEngine/ImageCache.h>

#include "DialogTree.h"

#include <iostream>

int main()
{
	TxtEgn::InputControl _Input;
	TxtEgn::ImageCache Cache(_Input);
	TxtEgn::ConsoleProp _Console;
	_Console.Init(10, 16, 0, 0, 7, false);
	TxtEgn::COutput _OutputB(_Console, _Input, Cache);

	DialogTree First(_OutputB, "Dialog/Test.json");
	First.Init();
	First.PerformDialog();

	int a;
	std::cin >> a;

	return 0;
}
//
//int rv = First.PerformDialog();
//_OutputB.WriteSlow("" + rv, true);
//_OutputB.DrawImage("Images/MafiaDen.txt", TxtEgn::ALIGN::LEFT);
//_OutputB.DrawImage("Images/MafiaDen.txt", TxtEgn::ALIGN::LEFT);


//_ConsoleZoneA.Init(50, 0, 7, 7, 10, 16, 12); 

//_Console.Init(16, 22, 0, 0, 7, true);
//_Console.SetConsoleWidth(_Console.FindConsoleWidth());

//COutput _OutputA(_ConsoleZoneA, _Input, Cache);
//

//_OutputB.DrawImage("Images/MafiaDen.txt", TxtEgn::ALIGN::CENTER);
//_OutputB.DrawImage("Images/MainTitle.txt", TxtEgn::ALIGN::LEFT);
//_OutputB.DrawImage("Images/MainTitle.txt", TxtEgn::ALIGN::RIGHT);

//_OutputB.WriteSlow("<C123> Hello <C12> my name <C/> is ", true);