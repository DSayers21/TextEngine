#include "MainGame.h"

MainGame::MainGame(std::string FilePath, bool NewPlayer, TxtEgn::InputControl* Input, TxtEgn::ConsoleProp* Console, TxtEgn::ImageCache* Cache, TxtEgn::COutput* Output)
{
	m_Cache = Cache;
	m_Input = Input;
	m_Console = Console;
	m_Output = Output;

	m_Game.Load(FilePath);

	if (NewPlayer)
	{
		std::string PlrName = m_Input->ParseIntoSentence(m_Output->GetInput("<C10>What is your name?"), 0);

		m_Player = Player(PlrName, 1, 100);
		Item Test("Test Item", "This Item is to Test the columns, if this is working there should be multiple lines wooooo. And maybe even 3 of them like all below one another in a list", 100, false);
		m_Player.AddItem(Test);
	}
	else
	{
		m_Player.Load(FilePath);
	}
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
	
	m_Output->DisplayBanner(207, m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "[Type 'HELP' to see a full list of known commands]"), true);
	
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
				case 0:			//Go Command
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
				case 1:			//Take Command
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						m_CurrentLocation->PickUpItem(m_Output, &m_Player, Temp);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a item", true);
					break;
				}
				case 2:			//Quit Command
				{
					GameRunning = false;
					std::string Test = m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "Game Quitted");
					m_Output->DisplayBanner(207, Test, true);
					break;
				}
				case 3:			//Look Command
				{
					m_CurrentLocation->DisplayAll(m_Output);
					break;
				}
				case 4:			//Clear Command
				{
					m_Output->ConsoleClear();
					break;
				}
				case 5:			//Help Command
				{
					std::string Left, Middle, Right, Output;
					int TempSize;

					m_Output->DisplayBanner(240, m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "Command List"), false);
					int VecSizeTemp = static_cast<int>(Command.size());

					if (VecSizeTemp % 3 == 0)
						TempSize = VecSizeTemp;
					else
						(VecSizeTemp + 1 % 3 == 0) ? TempSize = (VecSizeTemp + 1) : TempSize = (VecSizeTemp + 2);

					for (int i = 0; i < TempSize; i += 3)
					{
						Left = m_Input->AlignLeft(' ', m_Output->GetConsole()->GetConsoleWidth(), "[" + Command[i] + "]");

						if ((i + 1 < TempSize) && (i + 1 < VecSizeTemp))
							Middle = m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "[" + Command[i + 1] + "]");
						else
							Middle = m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), " ");
						if ((i + 2 < TempSize) && (i + 2 < VecSizeTemp))
							Right = m_Input->AlignRight(' ', m_Output->GetConsole()->GetConsoleWidth(), "[" + Command[i + 2] + "]");
						else
							Right = m_Input->AlignRight(' ', m_Output->GetConsole()->GetConsoleWidth(), " ");

						Output = m_Input->CombineString(Left, Right);
						Output = m_Input->CombineString(Output, Middle);
						m_Output->DisplayBanner(112, Output, true);
					}
					m_Output->GetConsole()->SetColour(7);
					m_Output->GetConsole()->Update();
					break;
				}
				case 6:			//Stats Command
				{
					m_Player.Display(m_Output);
					break;
				}
				case 7:			//Drop Command
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						m_Player.DropItem(m_Output, m_CurrentLocation, Temp);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a item", true);
					break;
				}
				case 11:		//Colours Command
				{
					for (int i = 0; i < 255; i++)
					{
						m_Output->GetConsole()->SetColour(i);
						if (i < 10)
							std::cout << " ";
						if (i < 100)
							std::cout << " ";
						std::cout << std::to_string(i);
						if (i % 15 == 0)
							std::cout << std::endl;
					}
					std::cout << std::endl;
					m_Output->GetConsole()->SetCurrentY(m_Output->GetConsole()->wherey());
					break;
				}
			}
		}
	}
	return 0;
}