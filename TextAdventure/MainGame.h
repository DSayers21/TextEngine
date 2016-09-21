#pragma once
#include "GameWorld.h"
#include "Location.h"
#include "Player.h"
#include <vector>
#include <string>
#include <TextEngine/InputControl.h>
#include <TextEngine/COutput.h>
#include <TextEngine/ConsoleProp.h>
#include <TextEngine/ImageCache.h>

class MainGame
{
public:
	MainGame(std::string FilePath, bool NewPlayer, TxtEgn::InputControl* Input, TxtEgn::ConsoleProp* Console, TxtEgn::ImageCache* Cache, TxtEgn::COutput* Output);
	~MainGame();

	void StartGame();

private:
	bool GameLoop();

	GameWorld m_Game;
	Location* m_CurrentLocation = nullptr;
	Player m_Player;

	std::vector<std::string> Direction{ "North", "South", "West", "East", "Up", "Down", "North West", "North East", "Out" };
	std::vector<std::string> Command{ "Go", "Take", "Quit", "Look", "Clear", "Help", "Stats", "Drop", "Push", "Pull",
		"Unlock","Colours", "Hello", "Hi", "Hey", "Howdy", "Search", "Inspect", "Give", "Save" };

	TxtEgn::InputControl* m_Input;
	TxtEgn::ConsoleProp* m_Console;
	TxtEgn::ImageCache* m_Cache;
	TxtEgn::COutput* m_Output;
	InOutDataManager m_IOMan;
};

