#include <TextEngine/ConsoleProp.h>
#include <TextEngine/COutput.h>
#include <TextEngine/InputControl.h>
#include <TextEngine/ConsoleZone.h>
#include <TextEngine/ImageCache.h>

#include "GameWorld.h"
#include "MainGame.h"

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

void ResetMenu(TxtEgn::COutput* Output, std::vector<std::string> Command);
bool dirExists(const std::string& dirName_in);

int main()
{
	//Set up input output methods
	TxtEgn::InputControl _Input;
	TxtEgn::ImageCache Cache(_Input);
	TxtEgn::ConsoleProp _Console;
	_Console.Init(10, 16, 0, 0, 7, true);
	TxtEgn::COutput _Output(_Console, _Input, Cache);

	//Menu Stuff
	std::vector<std::string> CurCommand;
	std::vector<std::string> Command = { "New", "Load", "Quit", "Help" };
	bool Running = true;

	//Draw title
	ResetMenu(&_Output, Command);

	//Init MainGame
	while (Running)
	{
		CurCommand.clear();
		CurCommand = _Output.GetInput("<C7>");

		if (CurCommand.size() > 0)
		{
			switch (_Input.ContainsString(Command, _Input.ParseIntoSentence(CurCommand, 0)))
			{
				default:
				{
					_Output.WriteSlow("<C12>You need to enter a valid Command", true);
					break;
				}
				case 0:			//New
				{
					MainGame Game("CloudGame", true, &_Input, &_Console, &Cache, &_Output);
					_Output.ConsoleClear();
					Game.StartGame();
					ResetMenu(&_Output, Command);
					break;
				}
				case 1:			//Load
				{
					std::string Path = _Input.ParseIntoSentence(_Output.GetInput("<C10>What is the name of the game?"), 0);
					if (dirExists(Path))
					{
						MainGame Game(Path, false, &_Input, &_Console, &Cache, &_Output);
						_Output.ConsoleClear();
						Game.StartGame();
						ResetMenu(&_Output, Command);
					}
					else
						_Output.WriteSlow("No data exists with that name!", true);
					break;
				}
				case 2:			//Quit
				{
					Running = false;
					break;
				}
				case 3:			//Help
				{
					_Output.DisplayTextBox(Command, '*', 7);
					break;
				}
			}
		}
	}
	return 0;
}

void ResetMenu(TxtEgn::COutput* Output, std::vector<std::string> Command)
{
	Output->ConsoleClear();
	Output->DrawImage("Images/MainTitle", TxtEgn::ALIGN::CENTER);
	Output->DisplayTextBox(Command, '*', 7);
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}