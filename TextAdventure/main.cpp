#include <TextEngine/ConsoleProp.h>
#include <TextEngine/COutput.h>
#include <TextEngine/InputControl.h>
#include <TextEngine/ConsoleZone.h>
#include <TextEngine/ImageCache.h>

#include "GameWorld.h"
#include "MainGame.h"

#include <iostream>

int main()
{
	//Set up input output methods
	TxtEgn::InputControl _Input;
	TxtEgn::ImageCache Cache(_Input);
	TxtEgn::ConsoleProp _Console;
	_Console.Init(10, 16, 0, 0, 7, true);
	TxtEgn::COutput _Output(_Console, _Input, Cache);

	//Draw title
	_Output.DrawImage("Images/MainTitle.txt", TxtEgn::ALIGN::CENTER);

	//Create GameWorld
	GameWorld CloudGame;
	//Load GameWorld
	CloudGame.Load("CloudGame");

	//Init MainGame
	MainGame Game(CloudGame, &_Input, &_Console, &Cache, &_Output);
	Game.StartGame();

	//End of game pause
	std::cout << " :: TYPE ANYTHING TO QUIT :: " << std::endl;
	int a;
	std::cin >> a;

	return 0;
}