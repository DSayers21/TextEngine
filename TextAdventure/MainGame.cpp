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
		//LoadPlayer
		m_Player.Load(FilePath);
	}
	//Get Current Location
	boost::property_tree::ptree Tree = m_IOMan.LoadFile(FilePath + "/CurLoc");
	std::string CurrentLoc = Tree.get<std::string>("CurrentLocation");
	m_CurrentLocation = m_Game.FindLocation(CurrentLoc);
}

MainGame::~MainGame()
{

}

void MainGame::StartGame()
{
	if(m_CurrentLocation == nullptr)
		m_CurrentLocation = m_Game.GetFirstLocation();

	m_Output->DrawImage(m_Game.GetImage(), TxtEgn::ALIGN::CENTER);
	GameLoop();
}

bool MainGame::GameLoop()
{
	bool GameRunning = true;
	std::vector<std::string> CurCommand;

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
				case 0:									//Go Command
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
				case 1:									//Take Command
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
				case 2:									//Quit Command
				{
					GameRunning = false;
					std::string Test = m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "Game Quitted");
					m_Output->DisplayBanner(207, Test, true);
					break;
				}
				case 3:									//Look Command
				{
					//Draw location image
					if (m_CurrentLocation->HasImage())
						m_Output->DrawImage(m_CurrentLocation->GetImage(), TxtEgn::ALIGN::CENTER);
					m_CurrentLocation->DisplayAll(m_Output);
					break;
				}
				case 4:									//Clear Command
				{
					m_Output->ConsoleClear();
					break;
				}
				case 5:									//Help Command
				{
					m_Output->DisplayBanner(240, m_Input->AlignCenter(' ', m_Output->GetConsole()->GetConsoleWidth(), "Command List"), false);

					unsigned int Column = 0; //0 is left, 1 is middle, 2 is right
					bool RowComplete = false;
					std::string Left = "", Right = "", Middle = "";

					for (int i = 0; i < Command.size(); i++)
					{
						switch (Column)
						{
							case 0:
							{
								Column = 1;
								Left = Command[i];
								break;
							}
							case 1:
							{
								Column = 2;
								Middle = Command[i];
								break;
							}
							case 2:
							{
								Column = 0;
								Right = Command[i];
								RowComplete = true;
								break;
							}
						}
						if(i+1 == Command.size())
							RowComplete = true;

						if (RowComplete)
						{
							RowComplete = false;
							m_Output->DisplayColumns3(Left, Middle, Right, 112, TxtEgn::ALIGN::CENTER);
							Left = "", Right = "", Middle = "";
						}
					}

					m_Output->GetConsole()->SetColour(7);
					m_Output->GetConsole()->Update();
					break;
				}	
				case 6:									//Stats Command
				{
					m_Player.Display(m_Output);
					break;
				}	
				case 7:									//Drop Command
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
				case 8: case 9: case 16:				//Push And Pull Search Command
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						Object* Obj = m_CurrentLocation->FindObject(Temp);
						Obj->ObjectCommand(m_Output, &m_Game, CurCommand[0], &m_Player, m_CurrentLocation);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a object", true);
					break;
				}
				case 10:								//Unlock
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						m_CurrentLocation->CommandObject(m_Output, &m_Game, CurCommand[0], Temp, &m_Player);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a object", true);

					break;
				}
				case 11:								//Colours Command
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
				case 12: case 13: case 14: case 15:		//Hello, hi, hey, howdy
				{
					if (CurCommand.size() > 1)
					{
						std::string Temp = m_Input->ParseIntoSentence(CurCommand, 1);
						NPC* Found = m_CurrentLocation->FindNPC(Temp);
						if(Found != nullptr)
							Found->StartConversation(m_Output, &m_Player);
						else
							m_Output->WriteSlow("<C12>No one exists of that name", true);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter someone to talk to", true);

					break;
				}
				case 17:								//Inspect Item
				{
					if (CurCommand.size() > 1)
					{
						bool Found = false;
						//Inspect Current Location
						Found = m_CurrentLocation->InspectAll(m_Output, m_Input->ParseIntoSentence(CurCommand, 1));
						//Inspect BackPack
						if (!Found)
							Found = m_Player.InspectAll(m_Output, m_Input->ParseIntoSentence(CurCommand, 1));
						//Nothing Found
						if (!Found)
							m_Output->WriteSlow("<C12>Could not find " + m_Input->ParseIntoSentence(CurCommand, 1)
								+ " in the current area", true);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter a item to inspect", true);
					break;
				}
				case 18:								//Give Item
				{
					if (CurCommand.size() > 1)
						m_CurrentLocation->GivetoNPC(m_Input->ParseIntoSentence(CurCommand, 1), m_Output, &m_Player);
					else
						m_Output->WriteSlow("<C12>You need to enter a item to give", true);
					break;
				}
				case 19:								//Save Command
				{
					std::string SaveName = m_Input->ParseIntoSentence(m_Output->GetInput("<C10> What do you want to save the file as?"), 0);
					
					m_Game.Save(SaveName, &m_Player);
					
					//Create Main Tree and Nodes tree
					boost::property_tree::ptree Tree;
					//Add the Conversation name to the top of the tree
					Tree.put("CurrentLocation", m_CurrentLocation->GetName());
					//Save the tree to a readable format
					m_IOMan.SaveFile(SaveName + "/CurLoc", Tree);

					m_Output->DisplayBanner(207, m_Input->AlignCenter(' ', m_Output->GetConsole()->FindConsoleWidth(), 
						"Game Saved"), true);
					break;
				}
				case 20:								//Battle Command
				{
					if (CurCommand.size() > 1)
					{
						Enemies* Find = m_CurrentLocation->FindEnemy(m_Input->ParseIntoSentence(CurCommand, 1));
						if(Find != nullptr)
							m_BattleField.Encounter(m_Output, &m_Player, Find);
						else
							m_Output->WriteSlow("<C7>You look around but do not notice anything by that name in the area.", true);
					}
					else
						m_Output->WriteSlow("<C12>You need to enter the name of what you want to battle", true);
					break;
				}
			}
		}
	}
	return 0;
}