#include "COutput.h"
#include "InputControl.h"
#include "Pixel.h"

#include <chrono>
#include <thread>

namespace TxtEgn
{
	COutput::COutput() : _Speed(10)
	{
	}

	COutput::COutput(ConsoleProp& Console, InputControl& Input, ImageCache& Cache) :
		_Console(&Console),
		_Input(&Input),
		_Cache(&Cache),
		_Speed(30)
	{

	}

	COutput::~COutput()
	{
	}

	void COutput::DisplayBanner(int Colour, std::string Statement, bool EndL)
	{
		_Console->SetColour(Colour);
		//Run WriteSlow Function
		std::cout << Statement;
		if (EndL)
			_Console->EndLine();
		_Console->SetColour(_Console->GetPrevColour());
	}

	void COutput::WriteSlow(std::string DisplayString, bool EndL, ALIGN Align, bool CompLine)
	{
		std::vector<std::string> Words = _Input->ParseIntoWords(DisplayString);

		std::string CurrentLine = "";
		std::vector<std::string> Lines;
		std::vector<int> LineLengths;

		int StartX = _Console->wherex();
		int CurX = StartX;
		int ConStrtX = _Console->GetStartX();


		int Size = static_cast<int>(Words.size());

		int CurSize = 0;

		for (int i = 0; i < Size; i++)
		{
			//Test for Colour Tags
			if ((Words[i].size() > 3) && (TestTag(Words[i]) == 2))
			{
				CurrentLine += Words[i];
			}
			else if ((Words[i].size() > 3) && (TestTag(Words[i]) == 1))
				CurrentLine += Words[i];
			else
			{
				if (CurSize + CurX + Words[i].size() < _Console->GetConsoleWidth())
				{
					CurrentLine += Words[i];
					CurSize += Words[i].size();
					if (CurSize + CurX != _Console->GetConsoleWidth())
					{
						CurrentLine += " ";
						CurSize++;
					}	
				}
				else
				{
					std::cout << "";
					CurX = 0;
					LineLengths.push_back(CurSize);
					CurSize = 0;
					_Console->gotoxy(ConStrtX, _Console->wherey());
					Lines.push_back(CurrentLine);

					CurrentLine = "";
					CurrentLine += Words[i];
					CurSize += Words[i].size();
					if (CurSize + CurX != _Console->GetConsoleWidth())
					{
						CurrentLine += " ";
						CurSize++;
					}
				}
			}
		}
		if((StartX > _Console->GetStartX())&&(StartX < _Console->GetConsoleWidth()))
			_Console->gotoxy(StartX, _Console->wherey());
		else
			_Console->gotoxy(_Console->GetStartX(), _Console->wherey());
		Lines.push_back(CurrentLine);
		LineLengths.push_back(CurSize);
		CurrentLine = "";
		DisplayAll(Lines, LineLengths, EndL, Align, CompLine);
	}

	void COutput::DisplayAll(std::vector<std::string> Lines, std::vector<int> LineLengths, bool EndL, ALIGN Align, bool CompLine)
	{
		for (int i = 0; i < Lines.size(); i++)
		{
			if ((i == Lines.size() - 1) && (!EndL))
				DisplayLine(Lines[i], LineLengths[i], Align, CompLine);
			else
			{
				DisplayLine(Lines[i], LineLengths[i], Align, CompLine);
				//Go to new line and update console
				GetConsole()->EndLine();
				GetConsole()->Update();
			}
		}
	}

	int COutput::AlignString(int Buffer, ALIGN Align)
	{
		switch (Align)
		{
			case ALIGN::LEFT:
			{
				return 0;
			}
			case ALIGN::RIGHT:
			{
				return Buffer;
			}
			case ALIGN::CENTER:
			{
				return Buffer/2;
			}
		}
	}

	void COutput::DisplayLine(std::string Line, int LineLength, ALIGN Align, bool CompLine)
	{
		std::vector<std::string> Words = _Input->ParseIntoWords(Line);
		std::string PrevStrings = "";

		//Align
		int Buff = _Console->GetConsoleWidth() - LineLength;
		Buff = AlignString(Buff, Align);
		for (int i = 0; i < Buff; i++)
			std::cout << " ";

		int Size = static_cast<int>(Words.size());

		for (int i = 0; i < Size; i++)
		{
			//Test for Colour Tags
			if ((Words[i].size() > 3) && (TestTag(Words[i]) == 2))
				_Console->RevertColour();
			else if ((Words[i].size() > 3) && (TestTag(Words[i]) == 1))
				SetTag(Words[i]);
			else
			{
				TypeString(Words[i]);
				if (_Console->wherex() != _Console->GetConsoleWidth())
					std::cout << " ";
			}
		}
		if (CompLine)
			CompleteLine(' ');
	}

	void COutput::TypeString(std::string DisplayString)
	{
		int Size = static_cast<int>(DisplayString.size());

		for (int i = 0; i < Size; i++)
		{
			std::cout << DisplayString[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(_Speed));
		}
	}

	//Write a line of characters across the screen
	void COutput::WriteLine(int Colour, char WriteChar)
	{
		//Set Colour to the colour passed to the function
		_Console->SetColour(Colour);
		//Go through each char space on screen and place char there
		for (int i = _Console->GetStartX(); i < _Console->GetConsoleWidth(); i++)
		{
			std::cout << WriteChar;
		}
		_Console->EndLine();
	}

	void COutput::CompleteLine(char FinChar)
	{
		int Buffer = _Console->GetConsoleWidth();
		int CurPos = _Console->wherex();

		for (int i = CurPos; i < Buffer; i++)
			std::cout << FinChar;
	}

	void COutput::DisplayTextBox(std::vector<std::string> SentText, char Surround, int Colour)
	{
		int InitY = _Console->wherey();
		int VecSize = static_cast<int>(SentText.size());
		std::string Space = "";
		std::string LEndCap = _Input->AlignLeft(' ', _Console->GetConsoleWidth(), Space + Surround);
		std::string REndCap = _Input->AlignRight(' ', _Console->GetConsoleWidth(), Surround + Space);
		std::string Output;

		WriteLine(Colour, Surround);
		for (int i = 0; i < VecSize; i++)
		{
			Output = _Input->CombineString(LEndCap, REndCap);
			Output = _Input->CombineString(Output, _Input->AlignCenter(' ', _Console->GetConsoleWidth(), SentText[i]));
			DisplayBanner(Colour, Output, false);
		}
		WriteLine(Colour, Surround);
		_Console->SetCurrentY(InitY + VecSize + 2);
		_Console->Update();
	}

	void COutput::ConsoleClear()
	{
		int PrevY = _Console->wherey();
		_Console->SetCurrentY(_Console->GetStartY());
		_Console->gotoxy(_Console->GetStartX(), _Console->GetStartY());
		for (int i = _Console->GetStartY(); i <= PrevY; i++)
		{
			WriteLine(0, ' ');
			_Console->gotoxy(_Console->GetStartX(), i);
		}
		_Console->gotoxy(_Console->GetStartX(), _Console->GetStartY());
	}

	void COutput::ConsoleClearLine()
	{
		int PrevX = _Console->wherex();
		_Console->gotoxy(_Console->GetStartX(), _Console->wherey());

		WriteLine(0, ' ');
		_Console->gotoxy(PrevX, _Console->wherey()-1);
		_Console->RevertColour();
	}

	std::vector<std::string> COutput::GetInput(std::string Question)
	{
		unsigned short TmpCol = _Console->GetColour();
		unsigned short PTmpCol = _Console->GetPrevColour();
		WriteSlow("<C10>" + Question + " <C7> " + ">", false);
		std::vector<std::string> InData = _Input->AskInput();

		_Console->SetCurrentY(_Console->wherey());
		_Console->Update();

		_Console->SetColour(TmpCol);
		_Console->SetPrevColour(PTmpCol);
		return InData;
	}

	void COutput::DrawImage(std::string Img, ALIGN Align)
	{
		//Get image from cache
		std::vector<Pixel> Image;
		ASCImage& AImg = _Cache->GetTexture(Img);
		Image = AImg.GetImage();

		int OFFx = ImageAlign(AImg, Align);

		int Width = AImg.GetWidth();

		//Display
		if (_Console->wherex() != _Console->GetStartX() + OFFx)
		{
			_Console->SetCurrentY(_Console->GetCurrentY() + 1);
			_Console->gotoxy(_Console->GetStartX(), _Console->GetCurrentY());
		}
		_Console->gotoxy(OFFx, _Console->GetCurrentY());

		int Count = _Console->GetStartX();

		for (int i = 0; i < Image.size(); i++)
		{
			_Console->SetColour(Image[i].GetColour());
			std::cout << Image[i].GetChar() << Image[i].GetChar();
			//std::this_thread::sleep_for(std::chrono::milliseconds(4));
			if (Count == Width - 1)
			{
				//Show Line
				_Console->EndLine();
				_Console->gotoxy(OFFx, _Console->GetCurrentY());
				Count = 0;
			}
			else
				Count++;
		}
		_Console->SetCurrentY(_Console->GetCurrentY() + 1);
		_Console->gotoxy(_Console->GetStartX(), _Console->GetCurrentY());
	}

	bool COutput::CheckIfOver(std::string DisplayString)
	{
		int TempSize = static_cast<int>(DisplayString.size());
		if (TempSize == _Console->GetConsoleWidth())
		{
			char First = DisplayString[0];
			char Last = DisplayString[TempSize - 1];

			if ((First == ' ') || (Last == ' '))
				return true;
		}
		return false;
	}

	int COutput::TestTag(std::string StringPassed)
	{
		char First, Second, Last, Special;
		int Size = static_cast<int>(StringPassed.size());

		First = StringPassed[0];
		Second = StringPassed[1];
		Special = StringPassed[2];
		Last = StringPassed[Size - 1];

		if ((First == '<') && (Second == 'C') && (Special == '/') && (Last == '>'))
			return 2;
		if ((First == '<') && (Second == 'C') && (Last == '>'))
			return 1;
		return 0;
	}

	void COutput::SetTag(std::string StringPassed)
	{
		int Size = static_cast<int>(StringPassed.size());
		std::string TagNum = "";

		for (int i = 0; i < Size; i++)
			if (isdigit(StringPassed[i]))
				TagNum = TagNum + StringPassed[i];
		_Console->SetColour(std::stoi(TagNum));
	}

	int COutput::ImageAlign(ASCImage Img, ALIGN Align)
	{
		switch (Align)
		{
		case ALIGN::LEFT:
			return 0;
			break;
		case ALIGN::CENTER:
			return ((_Console->GetConsoleWidth()) - Img.GetWidth() * 2) / 2;
			break;
		case ALIGN::RIGHT:
			return ((_Console->GetConsoleWidth() - Img.GetWidth() * 2));
			break;
		}
	}

	void COutput::DisplayColumns3(std::string Left, std::string Middle, std::string Right, int Colour, ALIGN Align)
	{
		//Init LowestY
		int LowestY = 0;
		//Get console width
		int ColWidth = _Console->FindConsoleWidth()*0.333;
		//Create Columns to output information to
		TxtEgn::COutput _OutputLeft = CreateColumn(ColWidth, 0, Colour);
		TxtEgn::COutput _OutputMiddle = CreateColumn(ColWidth, ColWidth, Colour);
		TxtEgn::COutput _OutputRight = CreateColumn(ColWidth+2, ColWidth*2, Colour);
		//Output information to columns whilst updating lowestY
		LowestY = _OutputLeft.DisplayColumn(Left, LowestY, Align);
		LowestY = _OutputMiddle.DisplayColumn(Middle, LowestY, Align);
		LowestY = _OutputRight.DisplayColumn(Right, LowestY, Align);
		//Set main console to the lowest position
		GetConsole()->SetCurrentY(++LowestY);
		GetConsole()->Update();
	}

	void COutput::DisplayColumnsConvo(std::string Left, std::string Right, int ColourA, int ColourB, ALIGN Align)
	{
		//Init LowestY
		int LowestY = 0;
		//Get console width
		int ColWidth = _Console->FindConsoleWidth()*0.333;
		//Create Columns to output information to
		TxtEgn::COutput _OutputLeft = CreateColumn(ColWidth, 0, ColourA);
		TxtEgn::COutput _OutputRight = CreateColumn(ColWidth*2+1, ColWidth, ColourB);
		//Output information to columns whilst updating lowestY
		LowestY = _OutputLeft.DisplayColumn(Left, LowestY, Align);
		LowestY = _OutputRight.DisplayColumn(Right, LowestY, Align);
		//Set main console to the lowest position
		GetConsole()->SetCurrentY(++LowestY);
		GetConsole()->Update();
	}

	COutput COutput::CreateColumn(int Width, int StartX, int Colour)
	{
		TxtEgn::ConsoleProp* _ConsoleCol = new TxtEgn::ConsoleProp();
		_ConsoleCol->Init(_Console->GetFontX(), _Console->GetFontY(), StartX, _Console->wherey(), Colour, false);
		_ConsoleCol->SetConsoleWidth(Width);
		_ConsoleCol->gotoxy(_ConsoleCol->GetStartX(), _ConsoleCol->GetStartY());

		TxtEgn::COutput _OutputCol(*_ConsoleCol, *_Input, *_Cache);
		return _OutputCol;
	}

	int COutput::DisplayColumn(std::string Statement, int LowestY, ALIGN Align)
	{
		GetConsole()->Update();
		WriteSlow(Statement, false, Align, true);
		//CompleteLine(' ');
		return (GetConsole()->wherey() > LowestY) ? GetConsole()->GetCurrentY() : LowestY;
	}

	int COutput::MenuOptions(std::vector<std::string> OptionList)
	{
		std::vector<std::string> CurCommand;

		CurCommand.clear();
		CurCommand = GetInput("<C7>");

		if (CurCommand.size() > 0)
			return _Input->ContainsString(OptionList, _Input->ParseIntoSentence(CurCommand, 0));
	}

	//Setters
	void COutput::SetConsole(ConsoleProp& Console)
	{
		_Console = &Console;
	}

	void COutput::SetInput(InputControl& Input)
	{
		_Input = &Input;
	}

	//Getters
	ConsoleProp* COutput::GetConsole()
	{
		return _Console;
	}
}