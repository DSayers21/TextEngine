#include "MainGame.h"

MainGame::MainGame(GameWorld Game, TxtEgn::InputControl* Input, TxtEgn::ConsoleProp* Console, TxtEgn::ImageCache* Cache, TxtEgn::COutput* Output)
{
	m_Cache = Cache;
	m_Input = Input;
	m_Console = Console;
	m_Output = Output;

	m_Game = Game;
}


MainGame::~MainGame()
{

}

void MainGame::StartGame()
{
	m_CurrentLocation = m_Game.GetFirstLocation();
	GameLoop();
}

bool MainGame::GameLoop()
{
	bool GameRunning = true;
	std::vector<std::string> CurCommand;
	//m_Output->WriteSlow("The quick brown fox jumped over the lazy dog The quick brown fox jumped over the lazy dog The quick brown fox jumped over the lazy dog The quick brown fox jumped over the lazy dog The quick brown fox jumped over the lazy dog lol", true);
	while (GameRunning)
	{
		CurCommand.clear();
		//Command------------------------------------------------------/
		CurCommand = m_Output->GetInput("<C7>");

		if (CurCommand.size() > 0)
		{
			switch (m_Input->ContainsString(Command, CurCommand[0]))
			{
				default:
					m_Output->WriteSlow("<C12>You need to enter a valid Command", true);
				break;
				case 0://Go Command
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						m_CurrentLocation = m_CurrentLocation->GoCommand(Temp);
						m_Output->WriteSlow("<C7> You see " + m_CurrentLocation->GetDesc(), true);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a direction", true);
					break;
				}
				case 2: //Quit
				{
					GameRunning = false;
					std::string Test = m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "Game Quitted");
					m_Output->DisplayBanner(207, Test, true);
					break;
				}
				case 3: //Look
				{
					m_CurrentLocation->DisplayAll(m_Output);
				}
			}
		}
	}
	return 0;
}