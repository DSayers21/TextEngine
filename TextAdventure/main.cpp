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
#include <tuple>
#include <windows.h>

void ResetMenu(TxtEgn::COutput* Output, std::vector<std::string> Command);
bool dirExists(const std::string& dirName_in);
void SettingsMenu(TxtEgn::COutput* Output);
void SetFont(TxtEgn::COutput* Output, int X, int Y);
void SaveFont(int X, int Y);
void LoadFont(TxtEgn::COutput* Output);

int main()
{
	//Set up input output methods
	TxtEgn::InputControl _Input;
	TxtEgn::ImageCache Cache(_Input);
	TxtEgn::ConsoleProp _Console;
	_Console.Init(10, 16, 0, 0, 7, true);

	TxtEgn::COutput _Output(_Console, _Input, Cache);
	//Load Font
	LoadFont(&_Output);

	//Menu Stuff
	std::vector<std::string> MenuCommand = { "New", "Load", "Settings", "Help", "Quit" };
	bool Running = true;

	//Draw title
	ResetMenu(&_Output, MenuCommand);

	//Init MainGame
	while (Running)
	{
		switch (_Output.MenuOptions(MenuCommand))
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
				ResetMenu(&_Output, MenuCommand);
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
					ResetMenu(&_Output, MenuCommand);
				}
				else
					_Output.WriteSlow("No data exists with that name!", true);
				break;
			}
			case 2:			//Settings
			{
				_Output.ConsoleClear();
				SettingsMenu(&_Output);
				ResetMenu(&_Output, MenuCommand);
				break;
			}
			case 3:			//Help
			{
				_Output.DisplayTextBox(MenuCommand, '*', 7);
				break;
			}
			case 4:			//Quit
			{
				Running = false;
				break;
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

void SettingsMenu(TxtEgn::COutput* Output)
{
	std::vector<std::string> SettingsOptions{ "5", "6", "8", "10", "12", "14", "16", "18", "20", "24", "28", "Back" };
	std::vector<std::string> SettingsOptionsTwo{ "2", "3", "4", "5", "6", "7", "8", "8", "9", "11", "13", "Back" };

	std::vector<std::string> ShowOPT{ ":5, 6, 8, 10, 12, 14, 16, 18, 20, 24, 28:", ":Back:" };
	int Position;
	TxtEgn::InputControl _Input;
	Output->DrawImage("Images/OptionsTitle", TxtEgn::ALIGN::CENTER);
	
	bool MenuLoop = true;

	Output->DisplayTextBox(ShowOPT, '*', 11);

	while (MenuLoop)
	{
		Position = Output->MenuOptions(SettingsOptions);
		switch (Position)
		{
			default:
			{
				Output->WriteSlow("<C12>You need to enter a valid Command", true);
				break;
			}
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
			{
				int X = std::stoi(SettingsOptionsTwo[Position]);
				int Y = std::stoi(SettingsOptions[Position]);
				SetFont(Output, X, Y);
				MenuLoop = false;
				break;
			}
			case 11:
			{
				MenuLoop = false;
				break;
			}
		}
	}
}

void SetFont(TxtEgn::COutput* Output, int X, int Y)
{
	Output->GetConsole()->SetFont(X, Y);
	Output->GetConsole()->SetConsoleWidth(Output->GetConsole()->FindConsoleWidth());
	Output->GetConsole()->ToggleFull();
	Output->GetConsole()->ToggleFull();
	SaveFont(X, Y);
}

void SaveFont(int X, int Y)
{
	InOutDataManager m_IOMan;
	boost::property_tree::ptree Tree;
	boost::property_tree::ptree FontSize;
	FontSize.put("X", X);
	FontSize.put("Y", Y);
	Tree.add_child("CurrentFont", FontSize);
	//Save the tree to a readable format
	m_IOMan.SaveFile("FontSizes", Tree);
}

void LoadFont(TxtEgn::COutput* Output)
{
	InOutDataManager m_IOMan;
	boost::property_tree::ptree Tree = m_IOMan.LoadFile("FontSizes");
	boost::property_tree::ptree FontSize = Tree.get_child("CurrentFont");
	int X = FontSize.get<int>("X");
	int Y = FontSize.get<int>("Y");
	SetFont(Output, X, Y);
}